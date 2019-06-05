#include "skiplist.h"

#include <fstream>
//to get more average time cost we design a skip list array to balance extreme conditions
#define LISTNUM 4
using namespace std;
using std::default_random_engine;
using std::uniform_real_distribution;

//factor controlling the probability
int rec_p;

void setFactorP(int p)
{
	rec_p = p;
}

SkipList* CreateSL(int inrec_p)
{
	SkipList *sl = new SkipList;
	if (sl == NULL)
		return NULL;
	sl->level = 0;
	//set the initial level of the skip list to 0
	Node* head = CreateNode(MAXLEVEL, 0);
	//create the head node
	if (head == NULL)
	{
		free(sl);
		return NULL;
	}
	sl->head = head;
	rec_p = inrec_p;
	//set random seed
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);
	return sl;
}

Node* CreateNode(int level, ElementType key)
{
	Node* newNode = new Node;
	newNode->forward = new Node*[level];
	for (int i = 0; i < level; i++)
	{
		newNode->forward[i] = NULL;
	}
	newNode->key = key;
	return newNode;
}

int RandomLevel()
{
	int level = 1;
	while (level < MAXLEVEL && rand() % rec_p == 1)
	{
		level++;
	}
	level = (MAXLEVEL > level) ? level : MAXLEVEL;
	return level;
}

bool Insert(SkipList *sl, ElementType key)
{
	//the array used to record the search route to insert a node or delete a node
	Node* update[MAXLEVEL];
	//pos points to forward node of ppos
	Node *pos = NULL;
	Node *ppos = sl->head;
	int i = sl->level - 1;
	/**************************step 1*************************/
	/* search for the node with value key from the highest level
	* and update the array "update" with node having been visited
	* which means saving those node where the level decreases to array "update"
	*/
	for (; i >= 0; i--)
	{
		while (((pos = ppos->forward[i]) != NULL) && pos->key < key)
		{
			ppos = pos;
		}
		update[i] = ppos;
	}
	//if the node with value key already exists then return true directly
	if ((pos != NULL) && pos->key == key)
	{
		return true;
	}
	/**************************step 2*************************/
	//generate a random level
	int level = RandomLevel();
	//printf("key = %d and level = %d\n", key, level);
	//if the new level is greater than current level of skip list
	if (level > sl->level)
	{
		for (i = sl->level; i < level; i++)
		{
			//make the node in new level i point to head node
			update[i] = sl->head;
		}
		sl->level = level;
	}
	/**************************step 3*************************/
	//create a new node with value key
	pos = CreateNode(level, key);
	if (!pos)
		return false;
	/* the new node must be inserted into every level i where it appears
	* and in level i, its pre position is stored in update[i]
	*/
	for (i = level - 1; i >= 0; i--)
	{
		pos->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = pos;
	}
	//free(pos);
	return true;
}

bool Delete(SkipList *sl, ElementType key)
{
	//the array used to record the search route to insert a node or delete a node
	Node* update[MAXLEVEL];
	Node *pos = NULL;
	Node *ppos = sl->head;
	int i = sl->level - 1;
	for (; i >= 0; i--)
	{
		while (((pos = ppos->forward[i]) != NULL) && pos->key < key)
		{
			ppos = pos;
		}
		update[i] = ppos;
	}
	//to see if it is the key node to be deleted
	if ((pos == NULL) || ((pos != NULL) && pos->key != key))
		return false;
	/* the new node must be deleted from every level i where it appears
	* and in level i, the nearest node with certain key value smaller than key is stored in update[i]
	*/
	for (i = sl->level - 1; i >= 0; i--)
	{
		if (update[i]->forward[i] == pos)
		{
			update[i]->forward[i] = pos->forward[i];
			//if the node to be deleted happens to be in the highest level and is the only node in that level
			if (sl->head->forward[i] == NULL)
				sl->level--;
		}
	}
	free(pos);
	//pos = NULL;
	return true;
}

void Search(SkipList *sl, ElementType key)
{
#if !DEBUG

	//the array used to record the search route to search for a node
	ElementType route[MAX][2];
#endif
	Node *pos = NULL;
	Node *ppos = sl->head;
	int i = sl->level - 1;
#if !DEBUG
	int j = 0;
#endif
	for (; i >= 0; i--)
	{
		while (((pos = ppos->forward[i]) != NULL) && pos->key < key)
		{
			ppos = pos;
#if !DEBUG
			route[j][0] = i;
			route[j][1] = pos->key;
			j++;
#endif
		}
		if ((pos != NULL) && pos->key == key)
		{
#if !DEBUG
			route[j][0] = i;
			route[j][1] = pos->key;
			PrintTrace(route,j);
#endif
			return;
		}
	}
#if !DEBUG
	printf("\t\t Couldn't find the key node.\n");
	PrintTrace(route, j);
#endif
}

//print the route searching for the node with value key
void PrintTrace(ElementType route[][2], int row)
{
	printf("Route for searching:\n");
	for (int i = 0; i <= row; i++)
	{
		printf("Level:%d, key:%d\t", route[i][0] + 1, route[i][1]);
	}
	printf("\n\n");
}

void Print(SkipList *sl)
{
	Node *pos;
	int cnt = 1;
	int i = sl->level - 1;
	printf("Print SkipList:\n");
	for (; i >= 0; i--)
	{
		pos = sl->head->forward[i];
		printf("Level %d:\n", i + 1);
		
		while (pos != NULL)
		{
			cnt++;
			if (cnt % 10 == 0) {
				printf("\n");
				
			}
			printf("key:%d\t", pos->key);
			pos = pos->forward[i];
		}
		printf("\n");
	}
	printf("\n");
}

void Free(SkipList *sl)
{
	if (!sl)
		return;
	Node *tmp = sl->head;
	Node *nxt;
	while (tmp != NULL)
	{
		nxt = tmp->forward[0];
		free(tmp);
		tmp = nxt;
	}
	free(sl);
}

//for test
void test()
{
	int rec_p;
	int num;
	vector<ElementType> vec;
	vector<ElementType> keys;
	clock_t start, end;
	double costInsert, costDelete, costSearch;
	int loop = 8;
	int exp = 3;
	int stand = 0;
	SkipList *sl[LISTNUM][3];
	for (int j = 0; j < LISTNUM; j++)
	{
		//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		for (int k = 0; k < 3; k++) 
		{			
			//printf("generating seed = %d\n", seed);
			sl[j][k] = CreateSL((int)(pow(2, k + 1)));
		}
	}
	printf("***************************Skip List Testing***************************\n");
	printf("The test data will be run from 1...500 to 1...1000000.\n");

	for (int cases = 1; cases <= loop; cases++) {
		costInsert = 0; costDelete = 0; costSearch = 0;
		//DEBUG Model: gerenate num for testing
		num = (cases % 2 == 1) ? (int)(pow(10, exp)) / 2 : (int)(pow(10, exp));
		if (cases % 2 == 0)
			exp++;
		for (int i = stand + 1; i <= num; ++i)
		{
			vec.push_back(i);
			keys.push_back(i);
		}
		//with the test size going up, we add new num to original lists rather than recreate new lists to maintain a relatively similiar structure during the whole test
		stand = num;
		for (int k = 0; k < 3; k++) {
			printf("num samples: %d, p: 1/%d \n", num, (int)(pow(2, k + 1)));
			setFactorP((int)(pow(2, k + 1)));
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			//1.insert N nodes into the skip lists to initialize
			//2.add nodes to existing skip lists
			for (int j = 0; j < LISTNUM; j++)
			{
				for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
					Insert(sl[j][k], *it);
				}
			}

			// delete insert search(random element)
			clock_t instart, inend, destart, deend;
			srand(seed);
			for (int j = 0; j < LISTNUM; j++)
			{
				//loop every single operation for 100000 times
				for (int z = 0; z < 100000; z++)
				{
					int random = rand();
					int deletekey = *(keys.begin() + random % keys.size());
					destart = clock();
					Delete(sl[j][k], deletekey);
					deend = clock();
					costDelete += (deend - destart) / (double)(CLOCKS_PER_SEC / 1000);
					instart = clock();
					Insert(sl[j][k], deletekey);
					inend = clock();
					costInsert += (inend - instart) / (double)(CLOCKS_PER_SEC / 1000);
					//generate random searchkey for test
					int searchkey = *(keys.begin() + random % keys.size());
					start = clock();
					Search(sl[j][k], searchkey);
					end = clock();
					costSearch += (end - start) / (double)(CLOCKS_PER_SEC / 1000);
				}
			}
			printf("insert cost(random):%f second\n", costInsert / (100000 * LISTNUM));
			printf("delete cost(random):%f second\n", costDelete / (100000 * LISTNUM));
			printf("search cost(random):%f second\n", costSearch / (100000 * LISTNUM));
			printf("------------------------------------------\n");
		}
		vec.clear();
	}
	for (int j = 0; j<LISTNUM; j++)
		for (int k = 0; k < 3; k++)
			Free(sl[j][k]);
	printf("*****************************Testing over!*****************************\n");
}
