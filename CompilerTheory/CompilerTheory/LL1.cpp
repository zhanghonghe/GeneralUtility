#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

#define	MY_ASSERT(x)	if(!(x)) {assert(0 && #x);}

struct Grammer{
	typedef std::pair< std::string, std::vector<std::string> > RULE;

	std::vector<RULE> rules;
};

void ExtractTerminal(Grammer const& grammer, std::map<std::string, bool> &isTerminal)
{
	for (auto it = grammer.rules.begin(), end = grammer.rules.end(); it != end; ++it)
	{
		isTerminal[it->first] = false;
		for (auto it2 = it->second.begin(), end2 = it->second.end(); it2 != end2; ++it2)
		{
			if (isTerminal.find(*it2) == isTerminal.end())
				isTerminal[*it2] = true;
		}
	}
}

void Union(std::set<std::string> const &l, std::set<std::string>  &r,bool &isChanged)
{
	//isChanged = false;
	std::for_each(l.begin(), l.end(), [&r, &isChanged](std::string const&s){
		if (r.find(s) == r.end()) { r.insert(s); isChanged = true; }
	});
}

template <class T>
static bool IsAllNullable(T begin, T end, std::map<std::string, bool> const &nullable)
{
	bool isAllYiNullable = true;
	for (T it = begin; it != end; ++it)
	{
		auto it2 = nullable.find(*it);
		if (it2 == nullable.end() || !it2->second)
		{
			isAllYiNullable = false; break;
		}
	}
	return isAllYiNullable;
}

void ComputeFirst(Grammer const& grammer, 
	std::map<std::string, std::set<std::string> > const &first,
	std::map<std::string, bool> const &nullable, 
	std::vector<std::string> const &f, std::set<std::string> &fFirst, bool &isNullable)
{
	fFirst.clear();
	bool isChanged;

	isNullable = true;
	//FIRST(X1X2...Xn)的计算方法：所有FIRST(Xi) (i=1,2,..,k)的并集，其中k为第一个具有性质ε不属于FIRST(Xk)的文法符号
	for (size_t i = 0, n = f.size(); i < n;i++)
	{
		auto Xi = f[i];
		auto it2 = first.find(Xi); // FIRST(Xi)
		if (it2 != first.end())	
		{
			Union(it2->second, fFirst, isChanged);
			auto it3 = nullable.find(it2->first);
			if (it3 != nullable.end() && it3->second)	//ε不属于FIRST(Xk)
			{
				isNullable = false;
				break;
			}
		}
	}
}

void ComputePredictTable(Grammer const& grammer, std::map<std::string, bool> const &isTerminal,
	std::map<std::string, std::set<std::string> > const &first, std::map<std::string, std::set<std::string> > const &follow,
	std::map<std::string, bool> const &nullable, std::map< std::pair<std::string, std::string>, Grammer::RULE > &table)
{
	for (auto it = grammer.rules.begin(), end = grammer.rules.end(); it != end; ++it)
	{
		std::set<std::string> fFirst;
		bool isNullable;
		bool isChanged;

		ComputeFirst(grammer, first, nullable, it->second, fFirst, isNullable);

		if (isNullable)
		{
			Union(follow.find(it->first)->second, fFirst, isChanged);
		}

		for (auto it2 = fFirst.begin(), end2 = fFirst.end(); it2!=end2;++it2)
		{
			table[std::make_pair(it->first, *it2)] = *it;
		}
	}
}

void FirstFollow(Grammer const& grammer, std::map<std::string, std::set<std::string> > &first, std::map<std::string, std::set<std::string> > &follow, std::map<std::string, bool> &nullable)
{
	// For each terminal Z: first(Z) <- Z
	std::map<std::string, bool> isTerminal;
	ExtractTerminal(grammer, isTerminal);
	std::for_each(isTerminal.begin(), isTerminal.end(), [&first](std::pair<const std::string, bool> &it){
		if (it.second)
			first[it.first].insert(it.first);
	});

	// Nullable
	for (auto it = isTerminal.begin(), end = isTerminal.end(); it != end; ++it)
	{
		if (!it->second)
			nullable[it->first] = false;
	}

	for (auto it = grammer.rules.begin(), end = grammer.rules.end(); it != end; ++it)
	{
		if (it->second.size() == 0)
			nullable[it->first] = true;
	}

	for (bool isStop = false; !isStop; )
	{
		isStop = true;

		for (auto it = grammer.rules.begin(), end = grammer.rules.end(); it != end; ++it)
		{
			bool isAllYiNullable = IsAllNullable(it->second.begin(), it->second.end(), nullable);
			
			if (isAllYiNullable)
			{
				MY_ASSERT(nullable.find(it->first) != nullable.end());
				if (!nullable[it->first])
				{
					nullable[it->first] = true;
					isStop = false;
				}
			}
		}
	}

	// First
	for (auto it = isTerminal.begin(), end = isTerminal.end(); it != end; ++it)
	{
		if (!it->second)
		{
			first[it->first].clear();
		}
		else //若X∈T（终结符），则FIRST(X)={X}
		{
			first[it->first].insert(it->first);
		}
	}

	for (;;)
	{
		bool isChanged = false;

		for (auto it = grammer.rules.begin(), end = grammer.rules.end(); it != end; ++it)
		{
			for (int i = 0, k = it->second.size(); i < k; i++)
			{
				if (k == 1)//若X是非终结符且有X → ε，则加ε到FIRST(X) (其实这里处理了右边只有一个元素的所有情况，ε只是其中一种)
				{
					Union(first[it->second[0]], first[it->first], isChanged);
				}
				else
				for (int j = i + 1; j < k; j++)//若X是非终结符且有X→Y1Y2...Yk，那么对所有j(1≤j<k)，若a∈FIRST(Yj + 1)且ε∈FIRST(Yi), 0ij则加入a到FIRST(X)。
				{
					// if Y0...Yi-1 is all nullable, then ...
					bool isAllYiNullable = IsAllNullable(it->second.begin(), it->second.begin() + i, nullable);
					if (isAllYiNullable)
						Union(first[it->second[i]], first[it->first], isChanged);
				}
			}

		}

		if (!isChanged)
			break;
	}

	// Follow
	for (auto it = isTerminal.begin(), end = isTerminal.end(); it != end; ++it)
	{
		follow[it->first].clear();
	}
	for (;;)
	{
		bool isChanged = false;

		for (auto it = grammer.rules.begin(), end = grammer.rules.end(); it != end; ++it)
		{
			for (int i = 0, k = it->second.size(); i < k; i++)
			{
				if (k == 1)
				{
					Union(follow[it->first], follow[it->second[0]], isChanged);
				}
				else
				for (int j = i+1; j < k; j++)
				{
					// Not sure whether is correct!
					bool isAllYiNullable2 = IsAllNullable(it->second.begin()+i+1, it->second.end(), nullable);
					if (isAllYiNullable2)
						Union(follow[it->first], follow[it->second[i]], isChanged);

					bool isAllYiNullable3 = IsAllNullable(it->second.begin() + i+1, it->second.begin() + j, nullable);
					if (isAllYiNullable3)
						Union(first[it->second[j]], follow[it->second[i]], isChanged);
				}
			}
			
		}

		if (!isChanged)
			break;
	}
}

static void AddRule(const char *first, const char *second[10], Grammer &gramer)
{
	Grammer::RULE rule;
	rule.first = first;
	for (int i = 0; i < 10 && second[i]; i++)
		rule.second.push_back(second[i]);
}

void Split(const char *l, const char *seperator, std::vector<std::string> &r)
{
	const char *p0 =l, *p1 = strstr(p0, seperator);
	for (; ; )
	{
		if (p1)
			r.push_back(std::string(p0, p1));
		else
		{
			r.push_back(std::string(p0));
			break;
		}

		p0 = p1 + strlen(seperator);
		p1 = strstr(p0, seperator);
	}
}

void Trim(std::string &s)
{
	size_t p1 = s.find_first_not_of(" \t");
	size_t p2 = s.find_last_not_of(" \t");

	if (p1 == std::string::npos)
		p1 = 0;

	if (p2 == std::string::npos)
		p2 = s.length();
	else
		p2++;

	s = s.substr(p1, p2 - p1);
}

static short AddRule(const char *expr,  Grammer &gramer)
{
	std::vector<std::string> r;
	Split(expr, "=", r);

	MY_ASSERT(r.size() == 2);

	std::for_each(r.begin(), r.end(), [](std::string &s){ Trim(s); });
	std::vector<std::string> r2;
	Split(r[1].c_str(), " ", r2);
	std::for_each(r2.begin(), r2.end(), [](std::string &s){ Trim(s); });
	
	if (r2.size() == 1 && r2[0].length() == 0)
		r2.clear();

	Grammer::RULE rule;
	rule.first = r[0];
	rule.second = r2;
	gramer.rules.push_back(rule);
	return 0;
}

static void Print(std::map<std::string, bool> const &nullable)
{
	printf("===%s===\n", "nullable");
	std::for_each(nullable.begin(), nullable.end(), [](std::pair<std::string, bool> const &l){
		if (l.second) printf("%s ", l.first.c_str());
	});
	printf("\n");
}
static void Print(std::map<std::string, std::set<std::string> > const &first, const char *prefix)
{
	printf("===%s===\n", prefix);
	std::for_each(first.begin(), first.end(), [](std::pair<std::string, std::set<std::string>> const &s){
		printf("%s:", s.first.c_str());
		std::for_each(s.second.begin(), s.second.end(), [](const std::string &s2){
			printf("%s ", s2.c_str());
		});
		printf("\n");
	});
}

void TestLL1()
{
	Grammer gramer;

	//AddRule("Z=d", gramer);
	//AddRule("Z=X Y Z ", gramer);
	//AddRule("Y=", gramer);
	//AddRule("Y=c", gramer);
	//AddRule("X= Y ", gramer);
	//AddRule("X=a", gramer);
	AddRule("L=E ; L", gramer);
	AddRule("L=", gramer);
	AddRule("E=T E2", gramer);
	AddRule("E2 = + T E2", gramer);
	AddRule("E2 = - T E2", gramer);
	AddRule("E2 =", gramer);
	AddRule("T = F T2", gramer);
	AddRule("T2 = * F T2", gramer);
	AddRule("T2 = / F T2", gramer);
	AddRule("T2 = mod F T2", gramer);
	AddRule("T2 =", gramer);
	AddRule("F =( E )", gramer);
	AddRule("F =id", gramer);
	AddRule("F =num", gramer);

	std::map<std::string, bool> isTerminal;
	ExtractTerminal(gramer, isTerminal);

	std::map<std::string, std::set<std::string> > first;
	std::map<std::string, std::set<std::string> > follow;
	std::map<std::string, bool> nullable;
	FirstFollow(gramer, first, follow, nullable);
	Print(first, "FIRST");
	Print(follow, "follow");
	Print(nullable);

	std::map< std::pair<std::string, std::string>, Grammer::RULE > table;
	ComputePredictTable(gramer, isTerminal, first, follow, nullable, table);
}
