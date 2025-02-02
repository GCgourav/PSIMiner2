/*****************************************************************
 *                      CODE WRITTEN BY                          *
 *                                                               *
 *             Antonio Anastasio Bruto da Costa                  *
 *     Formal Method Laboratory, Dept. of CSE, IIT Kharagpur     *
 *                                                               *
 *****************************************************************/

/* 
 * amsMinerStructs.h : Where all the Interval Arithmetic structures, 
 * and supporting methods are defined.
 */

//#define DEBUG_ON

#ifndef MAX_STR_LENGTH
	#define MAX_STR_LENGTH 10240
#endif


#ifndef AMS_STRUCTS_H
        #define AMS_STRUCTS_H

#include "structs.h"       

//A Truth Assignment
struct truthAssignmentStruct{
	int predicate_id;
	int position;
	int truth;
	int type;		/*
					Type0: Knowledge Predicates
					Type1: Learned Predicates
				*/
};

struct indexCouple{
	int target;
	int predicate;
	int type;
	int truth;
	struct indexCouple* next;
};

//List of Truth Assignments
struct truthAssignmentListStruct{
	struct truthAssignmentStruct* asgmt;
	struct truthAssignmentListStruct* next;
};

//A Left Inclusive, Right Exclusive Interval
struct intervalStruct{
	double l;
	double r;
};

//List of Intervals
struct intervalListStruct{
	struct intervalStruct* interval;
	struct intervalListStruct* next;
};

// List of Interval Lists
struct listOfIntervalListsStruct{
	struct intervalListStruct* trueList;
	struct intervalListStruct* falseList;
	struct listOfIntervalListsStruct* nextList;
};

struct treeNode{					// --------- DECISION BUCKET ----------
	struct truthAssignmentListStruct* truthList;	//List of Predicate Truths
	struct listOfIntervalListsStruct** listOfIntervalSets;	//True & False Lists for each predicate
	double **gains;					//All gain pairs <target-position,predicateID>
	double mean;
        double error;
	int targetInfluence;				//Target Position Context for the node: 0 if the target has no temporal shift.
	int splittingPredicate_id;			//Predicate over which the current node will be split for its children.
	double traceLength;				//Length of Trace
	int trueFalseFlag;				//Indicates if the dual mean also contributes an assertion when the error is zero.
	struct treeNode* left;
	struct treeNode* right;
	struct treeNode* parent;
	struct indexCouple* explored;
        int id;                                         //To keep track of the number of nodes created
        int truthValue;
	int predType;					//Type of predicate 0 if learned by knowledge, 1 otherwise.
	struct predicateDetail* learnedPredicates;	//Predicates learned by the predicate learning tool via Sim-Annealing
};

struct nodeList{
        struct treeNode* node;
        struct nodeList* next;
};

struct predicateDetail{
	struct PORV* predicate;
	double gain;
	int bucket;
	struct intervalListStruct* trueList;
	struct predicateDetail* next;	
};

struct assertionStruct{
	char assertion[MAX_STR_LENGTH];
	double correlation;
	double support;
	struct assertionStruct* next;
};

struct assertionStruct* createAssertionStruct();
struct assertionStruct* addToAsssertionList(struct assertionStruct* assertion, struct assertionStruct* root);

/*
struct iidentifier{		//Identifier Structure : Linked List used to store any generic list of identifiers
	unsigned int state;						//CSV Column - Offset of 1
	struct iidentifier* next;//Pointer to the next Identifier in the list or Null(If this is the last Identifier)
};
*/

/******************************Methods**********************************/

/*
//Identifiers
struct iidentifier* createIdentifier(unsigned int state);
struct iidentifier* addIdentifierToList(struct identifier* root, struct identifier* ID);
struct identifier* addToIdentifierList(struct identifier* root, unsigned int state);
int getIdentifierID(struct identifier* list, unsigned int state);
struct identifier* duplicateIdentifierList(struct identifier* root);
void freeIdentifierList(struct identifier* id);
char* containsIdentifier(struct identifier* list1, struct identifier* list2);
void printIdentifier(struct identifier* id);	
void printIdentifierList(struct identifier* id);
struct identifier* getIdentifierWithID(struct identifier* list, int id);
*/

//Truth Assignments
struct truthAssignmentStruct* createTruthAssignment(int predicate_id, int truth, int position);
void addToTruthAssignmentList(struct truthAssignmentListStruct** root, struct truthAssignmentListStruct* listItem);
struct truthAssignmentListStruct* getLastListOfTruthAssignmentList(struct truthAssignmentListStruct* root);
struct truthAssignmentListStruct* duplicateTruthAssignmentList(struct truthAssignmentListStruct* root);
int predicateInList(struct truthAssignmentListStruct* root, int predicate);
void printTruthList(struct truthAssignmentListStruct* root);
int  printTruthListForIndex(struct truthAssignmentListStruct* root, int index, FILE* fp, int andprinter);
int  writeTruthListForIndex(struct truthAssignmentListStruct* root, int index, char* str, int andprinter);
void printTruthListToFile(struct truthAssignmentListStruct* root);
void printTruthListToFilePtr(struct truthAssignmentListStruct* root, FILE* fp);
void sortTruthAssignmentList(struct truthAssignmentListStruct** root);
struct truthAssignmentListStruct* auxMergeTruthAssignmentList(struct truthAssignmentListStruct* a, struct truthAssignmentListStruct* b);
void listSplit(struct truthAssignmentListStruct* root, struct truthAssignmentListStruct** mid);
void purgeTruthList(struct truthAssignmentListStruct* root);
void purgeTruthListForTreeNode(struct treeNode* root);


//Index Couples
struct indexCouple* createIndexCouple(int target, int predicate);
void addToIndexCoupleList(struct indexCouple** root, struct indexCouple* listItem);
struct indexCouple* getLastOfIndexCoupleList(struct indexCouple* root);
int indexInList(struct indexCouple* root, int predicate, int target);
void printIndexCoupleList(struct indexCouple* root);
void printIndexCoupleListToFilePtr(struct indexCouple* root, FILE* fp);
struct indexCouple* duplicateIndexCouple(struct indexCouple* root);

//Intervals
struct intervalStruct* createIntervalStruct(double l, double r);
void printInterval(struct intervalStruct* interval);
void printIntervalToFilePtr(struct intervalStruct* interval,FILE* fp);
void deleteIntervalStruct(struct intervalStruct* interval);

//IntervalLists
struct intervalListStruct* createIntervalList(struct intervalStruct* interval);
void addToIntervalList(struct intervalListStruct** root, struct intervalListStruct* listItem);
struct intervalListStruct* addIntervalToList(struct intervalListStruct* root, struct intervalListStruct* listItem);
struct intervalListStruct* getLastIntervalInList(struct intervalListStruct* root);
void printIntervalList(struct intervalListStruct* list);
void printIntervalListToFilePtr(struct intervalListStruct* list, FILE* fp);
void deleteIntervalList(struct intervalListStruct* list);
struct intervalListStruct* flattenIntervalList(struct intervalListStruct* list);
struct intervalListStruct* duplicateIntervalList(struct intervalListStruct* list);
struct intervalListStruct* unionIntervalLists(struct intervalListStruct* list1, struct intervalListStruct* list2);
struct intervalListStruct* mergeIntervalLists(struct intervalListStruct* list1, struct intervalListStruct* list2);

//List of Interval Lists
struct listOfIntervalListsStruct* createListOfIntervalLists(struct intervalListStruct* trueList, struct intervalListStruct* falseList);
void addToListOfIntervalLists(struct listOfIntervalListsStruct** root, struct listOfIntervalListsStruct* listItem);
struct listOfIntervalListsStruct* addListToListOfIntervalLists(struct listOfIntervalListsStruct* root, struct listOfIntervalListsStruct* listItem);
struct listOfIntervalListsStruct* getLastListOfIntervalsInList(struct listOfIntervalListsStruct* root);
void printListOfIntervalLists(struct listOfIntervalListsStruct* list);
void printListOfIntervalListsToFilePtr(struct listOfIntervalListsStruct* list, FILE* fp);
void deleteListOfIntervalLists(struct listOfIntervalListsStruct* lists);
struct listOfIntervalListsStruct* duplicateIntervalSet(struct listOfIntervalListsStruct* root);
struct listOfIntervalListsStruct* unionIntervalSets(struct listOfIntervalListsStruct* list1, struct listOfIntervalListsStruct* list2);
struct intervalListStruct* flattenIntervalSet(struct listOfIntervalListsStruct* list);

//Intersection Computation
struct intervalStruct* intersectIntervals(struct intervalStruct* interval1, struct intervalStruct* interval2);
struct intervalListStruct* intersectIntervalList(struct intervalListStruct* list1, struct intervalListStruct* list2);
struct listOfIntervalListsStruct* intersectIntervalSet(struct listOfIntervalListsStruct* intervalSet1, struct intervalListStruct* intervalList2);

//Tree Node
struct treeNode* createTreeNode(
	struct truthAssignmentListStruct* truthList,
	struct listOfIntervalListsStruct** listOfintervalSets,
	int targetInfluence,
	int splittingPredicate_id,
	double traceLength,
	struct treeNode* left,
	struct treeNode* right);

//Node List
struct nodeList* createNodeList(struct treeNode* node);
void addToNodeList(struct nodeList** root, struct nodeList* listItem);
struct nodeList* addNodeToList(struct nodeList* root, struct treeNode* listItem);
struct nodeList* getLastNodeInList(struct nodeList* root);


//Support Methods
double maxFloat(double val1, double val2);
double minFloat(double val1, double val2);
double lengthOfIntervalList(struct intervalListStruct* list);
int countLists(struct listOfIntervalListsStruct* list);
void computeFalseLists(struct listOfIntervalListsStruct* list, double traceLength);
struct listOfIntervalListsStruct* getListAtPosition(struct listOfIntervalListsStruct* intervalLists, int target);
struct listOfIntervalListsStruct** getListsAtPosition(struct listOfIntervalListsStruct** listOfIntervalSets, int target);

//Mean
double mean(double intervalListLength, double traceLength);
double computeMean(struct listOfIntervalListsStruct** localIntervalSets, int target, double traceLength, struct intervalListStruct** influenceLists);
double computeFalseMean(struct listOfIntervalListsStruct** localIntervalSets, int target, double traceLength, struct intervalListStruct** influenceLists);

//Entropy and Error
double error(double mean);
double computeEntropy(struct listOfIntervalListsStruct** target, struct intervalListStruct** endMatchList);
double computeTrueEntropy(struct listOfIntervalListsStruct** target, struct intervalListStruct** endMatchList);
double computeFalseEntropy(struct listOfIntervalListsStruct** target, struct intervalListStruct** endMatchList);
double computeOverlapEntropy(struct listOfIntervalListsStruct** target, struct intervalListStruct** endMatchList);
double computeBinaryEntropy(struct listOfIntervalListsStruct** localIntervalSet, struct truthAssignmentListStruct* constraintList, int predicate_id, int pos);

//Gain
void computeAllGains(struct listOfIntervalListsStruct** localIntervalSet, int target, int *trueFalseFlag, double* bestGain, int i, int j, int PORVCount, struct treeNode* currentNode, double* falseEntropy, double* trueEntropy);
struct treeNode* findBestGain(struct listOfIntervalListsStruct** localIntervalSets, int target, int PORVCount, int N, struct treeNode* currentNode);

struct listOfIntervalListsStruct* computeConstrainedIntervalSet(struct listOfIntervalListsStruct* list, int predicate_id, int truth, struct truthAssignmentListStruct* constraintList);

//Minkowski Methods
struct intervalStruct* minkowskiSum(struct intervalStruct* interval, double l, double r);
struct intervalStruct* minkowskiDiff(struct intervalStruct* interval, double l, double r);

struct intervalStruct* minkowskiIntervalSum(struct intervalStruct* interval1, struct intervalStruct* interval2);
struct intervalStruct* minkowskiIntervalDiff(struct intervalStruct* interval1, struct intervalStruct* interval2);

struct intervalListStruct* minkowskiSumList(struct intervalListStruct* list, double l, double r);
struct intervalListStruct* minkowskiDiffList(struct intervalListStruct* list, double l, double r);

int amsMine(struct treeNode* root,int target, int numberOfPORVs, int N,int depth);
void printTreeNode(struct treeNode* node);
void printTreeNodeToFile(struct treeNode* node,int depth);
void printTreeNodeToFilePtr(struct treeNode* root,FILE* fp);
void printTree(struct treeNode* node);

FILE* processInput(int argc, char* argv[], int* N, double* K, int* depth, int repeatFlag);
FILE* processConfig(int argc, char* argv[]);

int getTarget(int numberOfPORVs);
double getTraceLength();
void prepareBackwardInfluenceTraces(struct listOfIntervalListsStruct** localIntervalSets, int target, int N, double K, int strict);
void prepareRoot(struct treeNode* root,struct listOfIntervalListsStruct** intervalSet, int target, int numberOfPORVs,int N);
void choicePause();

struct intervalListStruct* forwardInfluence(struct intervalListStruct* source, int i, double k, struct intervalListStruct* target);
struct intervalListStruct** computeForwardInfluenceForAnAssertion(struct treeNode* assertion,int targetID,double k);
struct intervalListStruct* computeForwardInfluenceForAnAssertionForTruth(struct treeNode* assertion,int targetID,double k,int truth);

int cfileexists(const char * filename);

//Support and Correlation
double getCorrelation(struct truthAssignmentListStruct* truthList, struct intervalListStruct* targetList);
double getCorrelationForTruth(struct truthAssignmentListStruct* truthList, struct intervalListStruct* targetList, int truth);

double getSupport(struct truthAssignmentListStruct* truthList, struct intervalListStruct* targetList);

int testCorrelationSupport(struct truthAssignmentListStruct* truthList, struct intervalListStruct* targetList);	//Returns 0 or 1 depending on whether the prefix has support and correlation quantities above thresholds.
int testCorrelationSupportForTruth(struct truthAssignmentListStruct* truthList, int truth);

//Pretty Printers for Assertions
struct intervalListStruct** computeBuckets(struct treeNode* node);
struct intervalStruct* computeTightSeparation(struct intervalListStruct* list1,struct intervalListStruct* list2, int pos);
struct intervalStruct* computeSeparationAnyMatch(struct intervalListStruct** bucket,int bucketPos,struct intervalListStruct** targetList, int targetPos, int smallestBucketID);
struct intervalStruct* computeBucketSeparation(struct intervalListStruct** bucket,struct intervalListStruct** list2, int pos1, int pos2, int smallestBucketID);
struct intervalStruct* widenIntervalSet(struct intervalListStruct* list);
//void printAssertionWithTruthToFile(FILE* fp, struct intervalListStruct* targetList, struct intervalListStruct* bucket[], int bucketCount, int truth, struct treeNode* node);
void printAssertionWithTruthToFile(FILE* fp, struct intervalListStruct** targetList, struct intervalListStruct** bucket, int bucketCount, int truth, struct treeNode* node,int position);
void writeAssertionWithTruthToStruct(struct assertionStruct* assertion, struct intervalListStruct** targetList, struct intervalListStruct** bucket, int bucketCount, int truth, struct treeNode* node,int position);
void printAssertions(struct treeNode* node, FILE* fp);

void printFloatArrayToFile(double* array, int size, FILE* fp);
void printFloat2DArraryToFile(int size1, int size2, double array[][size2], FILE* fp);
void copyMatrix(double ** target, int m, int n, double source[][n]);

struct listOfIntervalListsStruct* getAllIntervalsFromFile(FILE* fp);
//struct indexCouple* findError(struct treeNode* node);

double getMaxIntervalList(struct intervalListStruct* list);
double getMaxIntervalSet(struct listOfIntervalListsStruct* set);

int getSmallestBucketID(struct truthAssignmentListStruct* truthtList);

FILE* getDTreeFilePtr();
struct intervalListStruct* endMatchForPrefix(struct truthAssignmentListStruct* constraintList);

//Predicate Detail
struct predicateDetail* createPredicateDetail(struct PORV* predicate, double gain, int bucket, struct intervalListStruct* trueList);
struct predicateDetail* addPredicateDetailToList(struct predicateDetail* root, struct predicateDetail* detail);
void printPredicateDetailToFilePtr(struct predicateDetail* detail,FILE* fp);
void printPredicateDetailListToFilePtr(struct predicateDetail* list,FILE* fp);
void deletePredicateDetails(struct predicateDetail* node);

void printRequestForNewPredicate(struct config* configuration, struct identifier* varList,  struct intervalListStruct** buckets, int bucketCount, struct intervalListStruct* targetTrueList);

void learnNewPredicates();
char* convertToDatFileName(char* temp);

double lengthOfIntervalLists(struct intervalListStruct **intervalLists);
struct intervalListStruct** endMatchesForPrefix(struct truthAssignmentListStruct* prefix);
struct intervalListStruct** createValidLists();

int checkCreateLogDir();
#endif