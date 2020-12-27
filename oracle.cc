/* Author: Imoleayo Abel
 * CS35 Lab 11
 * December 5, 2011
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>   // C++ file streams.
#include <sstream>   // For using a string as input stream.
#include "graph.h"
#include "graph-algorithms.h"
#include "hashtable.h"
#include <ctime>

using namespace std;

// set current year as a global variable
time_t now = time(0);
const int CURR_YEAR = 1900 + localtime(&now)->tm_year;

/*-------------------------- FUNCTION DEFINITIONS ---------------------------*/

int actorsAverageDistance(Graph<string*,string,int>* myGraph,
                          HashTable<string,string* >* actorsP);
int findTwoActorsPath(Graph<string*,string,int>* myGraph,
                      HashTable<string,string* >* actorsP);
int findMoviesActors(HashTable<string,vector<string>* >* myHash);
int findActorsMovies(HashTable<string,vector<string>* >* myHash);
HashTable<string,vector<string>* >* buildHashTable(char movieFile[]);
HashTable<string,string*>* 
buildActorHash(HashTable<string,vector<string>* >* myHash);
Graph<string*,string,int>*
buildGraph(HashTable<string,vector<string>* >* myHash,
           HashTable<string,string* >* actorsP);
string getRequest(int when);                    // get user inputs
void usage(char** argv);                        // Prints an error message.
vector<string> split(string line, char delim);  // Splits a line based on the
                                                // given character as delimiter 

/*----------------------------------------------------------------------------*/

int main(int argc, char** argv) {
  if (argc < 2) {      // check for right amount of command line arguments
    usage(argv);
    return 1;  
  }

  cout << "Building Tables..." << endl;

  /* hashtable with key = movie, value = pointer to vector of actors in movie */
  HashTable<string,vector<string>* >* myHash = buildHashTable(argv[1]);

  /* hashtable with keys = actor names, values = pointers to actor names */
  HashTable<string,string* >* actorsP = buildActorHash(myHash);

  cout << "Building Graph..." << endl;

  /* graph with vertices being pointers to name of actors */
  Graph<string*,string,int>* myGraph = buildGraph(myHash,actorsP);

  string request = getRequest(0);      // get user's first request
  int endCheck;            // 0 if functions run well, 1 if user chooses to quit
  while (request != "5") {
    if (request != "1" && request != "2" && request != "3" &&
        request != "4" && request != "5") {
      request = getRequest(2);  // ensure valid input
      continue;                 // restart while loop
    }
    if (request == "1") {
      endCheck = findActorsMovies(myHash);
    } else if (request == "2") {
      endCheck = findMoviesActors(myHash);
    } else if (request == "3") {
      endCheck = findTwoActorsPath(myGraph,actorsP);
    } else if (request == "4") {
      endCheck = actorsAverageDistance(myGraph,actorsP);
    }
    if (endCheck == 1) {        // if user opts to quit, end while loop
      break;
    }
    request = getRequest(1);
  }
  cout << endl;
  
  /* free memory */
  cout << "Freeing up memory..." << endl;
  List<vector<string>* >* hashValues = myHash->getValues();
  while (!hashValues->isEmpty()) {
    delete hashValues->removeHead();  // delete pointer to vector of actors
  }
  delete hashValues;                
  delete myHash;
  List<string* >* actorHashV = actorsP->getValues(); // pointers to actornames
  delete actorsP;
  while (!actorHashV->isEmpty()) {
    delete actorHashV->removeHead();                 // delete actorname
  }
  delete actorHashV;
  delete myGraph;
  return 0;
}

/*----------------------------------------------------------------------------*/

/**
 * findActorsMovies: Given an actor, pritns out all movies actor featured in
 *
 * Inputs: hashtable of movie-actors key-value pair
 *
 * Returns: 0 if user opts to quit program, 1 otherwise
 */
int findActorsMovies(HashTable<string,vector<string>* >* myHash) {
  cout << endl;
  cout << "Enter the name of an actor: ";
  string actor;
  getline(cin,actor);
  if (cin.eof()) {       // check if user opts to quit program
    return 1;
  }
  List<string>* hashKeys = myHash->getKeys();  // list of all movies
  cout << actor << endl;
  bool isActorInAnyMovie = false;
  while (!hashKeys->isEmpty()) {
    string movie = hashKeys->removeHead();
    vector<string>* movieActors = myHash->get(movie);
    for (int i = 0; i < movieActors->size(); i++) {
      if ((*movieActors)[i] == actor) {
        isActorInAnyMovie = true;
        cout << '\t' << movie << endl;
        break;
      }
    }
  }
  if (!isActorInAnyMovie) {     // if actor is not in any movie.
    cout << "\nThe actor you requested is not in our database." << endl;
  }
  delete hashKeys;
  return 0;
}

/*----------------------------------------------------------------------------*/

/**
 * findMoviesActors: Given a movie, prints all actors featured in the movie
 *
 * Inputs: hashtable of movie-actor key-value pairs
 *
 * Returns: 0 if user opts to quit program, 1 otherwise
 */
int findMoviesActors(HashTable<string,vector<string>* >* myHash) {
  cout << endl;
  string movie;
  cout << "Enter the title (AND year) of the movie (e.g. Starman 1984): ";
  getline(cin,movie);
  if (cin.eof()) {            // check if user opts to quit program
    return 1;
  }
  if (myHash->containsKey(movie)) {
    cout << movie << endl;
    vector<string>* movieActors = myHash->get(movie);
    for (int i = 0; i < movieActors->size(); i++) {  // print all actors
      cout << '\t' << (*movieActors)[i] << endl;
    }
  } else {
    cout << "\nThe movie you requested is not in our database.\n" << endl;
  }
  return 0;
}

/*----------------------------------------------------------------------------*/

/**
 * findTwoActorsPath: given two actors, finds the path between them. Supports
 *                    both unweighted and weighthed searches 
 * Inputs: graph of pointers to actors, hashtable of actor-pointer key-value
 *         pair
 * Returns: 0 if user opts to quit program, 1 otherwise
 */
int findTwoActorsPath(Graph<string*,string,int>* myGraph,
                      HashTable<string,string* >* actorsP) {
  cout << endl;
  cout << "Do you want paths weighted by movie production date?";
  cout << "\n\tYES/NO: ";
  string wgt;
  getline(cin,wgt);
  transform(wgt.begin(), wgt.end(), wgt.begin(), ::toupper);
  while (wgt != "YES" && wgt != "NO") {  // ensure valid input is entered
    if (cin.eof()) {                     // check if user opts to quit
      return 1;
    }
    cout << "error!  YES/NO: ";
    getline(cin,wgt);
    transform(wgt.begin(), wgt.end(), wgt.begin(), ::toupper);
  }
  cout << "First Actor: ";
  string firstActor, secondActor;
  getline(cin,firstActor);
  if (cin.eof()) {                        // check if user opts to quit
    return 1;
  }
  cout << "Second Actor: ";
  getline(cin,secondActor);
  if (cin.eof()) {                        // check if user opts to quit
    return 1;
  }
  if (firstActor == secondActor) {        // check for repeated actors
    cout << "\nYou entered the same actor twice.\n";
    return 0;
  }
  if (!actorsP->containsKey(firstActor) ||  // ensure graph contains both
      !actorsP->containsKey(secondActor)) { // actors
    cout << "\nAt least one of the actors enterred is not in our database.\n";
  }
  else {    
    string* firstActorp = actorsP->get(firstActor);    // get pointers to 
    string* secondActorp = actorsP->get(secondActor);  // actor names
    vector<string*> moviePath;     // variable to hold output of search
    if (wgt == "YES") {  // weighted search
      moviePath = weightedBfs(firstActorp,secondActorp,myGraph);
    }
    else if (wgt == "NO") { // unweighted search
      moviePath = bfs(firstActorp,secondActorp,myGraph);
    }
    if (moviePath.size() == 0) {  // if actors are in different components
      cout << "\nThe actors requested have no movie connections.\n";
    } else {
        string* actor1 = moviePath[0];
        cout << endl;
        for (int i = 1; i < moviePath.size(); i++) {
          string* actor2 = moviePath[i];
          string movie = myGraph->getEdge(actor1,actor2).getLabel();
          cout << '\t' << *actor1 << " was in "<< movie << " with " << *actor2;
          cout << endl;
          actor1 = actor2;
        }
      }
    }
  return 0;
}

/*----------------------------------------------------------------------------*/

/**
 * actorsAverageDistance: given an actor, finds aevrage distance of actor from 
 *                        other actors in database. Supports weighted and
 *                        unweighted distances
 * Inputs: graph of pointers to actors, hashtable of actor-pointer key-value
 *         pair
 * Returns: 0 if user opts to quit program, 1 otherwise
 */
int actorsAverageDistance(Graph<string*,string,int>* myGraph,
                          HashTable<string,string* >* actorsP) {
  cout << endl;
  cout << "Do you want distance weighted by movie production dates?";
  cout << "\n\tYES/NO: ";
  string wgt;
  getline(cin,wgt);
  transform(wgt.begin(), wgt.end(), wgt.begin(), ::toupper);
  while (wgt != "YES" && wgt != "NO") {    // ensure valid input
    if (cin.eof()) {                       // check if user opts to quit
      return 1;
    }
    cout << "error!  YES/NO: ";
    getline(cin,wgt);
    transform(wgt.begin(), wgt.end(), wgt.begin(), ::toupper);
  }
  cout << "Enter name of actor: ";
  string actor;
  getline(cin,actor);
  if (cin.eof()) {                        // check if user opts to quit
    return 1;
  }
  if (!actorsP->containsKey(actor)) {     // ensure actor is in database
    cout << "\nThe actor requested is not in our database.\n";
  } else {
    cout << endl;
    string* actorp = actorsP->get(actor);  // pointer to actor name
    if (wgt == "NO") { // unweighted search
      double dist = averageDistance(actorp,myGraph);
      cout << "\t" << actor << "'s average movie distance is: " << dist;
      cout << endl;
    }
    else if (wgt == "YES") { // weighted search 
      double dist = averageWeightedDistance(actorp,myGraph);
      cout << "\t" << actor << "'s average weighted movie distance is: " << dist;
      cout << endl;
    }
  }
  return 0;
}

/*----------------------------------------------------------------------------*/

/**
 * buildGraphs: builds graph of actor-pointer vertices with edges being the
 *              most recent movie between any two actors
 * Inputs: hashtable of movie-actors key-value pair and hashtable of
 *         actor-actor pointer key-value pair
 * Returns: Graph with actor-pointer vertices, and integer edge weights. The
 *          weight of an edge is CURR_YEAR minus year of movie production
 */
Graph<string*,string,int>* 
buildGraph(HashTable<string,vector<string>* >* myHash,
           HashTable<string,string* >* actorsP) {
  Graph<string*,string,int>* wgtGraph = new Graph<string*,string,int>;
  List<string>* hashKeys = myHash->getKeys();   // list of all movies
  while (!hashKeys->isEmpty()) {
    string movie = hashKeys->removeHead();
    vector<string> movieYear = split(movie,' ');
    stringstream ss(movieYear[movieYear.size() - 1]);
    int weight, year; ss >> year; weight = CURR_YEAR - year;
    vector<string>* actors = myHash->get(movie); // actors in movie
    for (int i = 0; i < actors->size(); i++) {
      string actor = (*actors)[i];
      string* actorp = actorsP->get(actor);   // pointer to actor
      if (!wgtGraph->containsVertex(actorp)) {
        wgtGraph->insertVertex(actorp);
      }
      for (int j = 0; j < i; j++) { // for all other actors before actor in list
        string otherActor = (*actors)[j];
        string* otherActorp = actorsP->get(otherActor);
        if (wgtGraph->containsEdge(actorp,otherActorp)) { // if edge exists
          int oldEdgeWeight = wgtGraph->getEdge(actorp,otherActorp).getWeight();
          if (oldEdgeWeight > weight) {  // create new edge if it weighs less
            wgtGraph->insertEdge(actorp,otherActorp,movie,weight);
            wgtGraph->insertEdge(otherActorp,actorp,movie,weight);
          }
        } else {  // if edge doesn't exist hitherto
          wgtGraph->insertEdge(actorp,otherActorp,movie,weight);
          wgtGraph->insertEdge(otherActorp,actorp,movie,weight);
        }
      }
    }
  }
  delete hashKeys;
  return wgtGraph;
}

/*----------------------------------------------------------------------------*/

/**
 * buildHashTable: builds hashTable of movie-pointer_to_vector_of_actors
 *                 key-value pair
 * Inputs: a tab separated file of actor names, and movies they featured in
 *
 * Returns: Hashtable with keys being movies and values being pointers to
 *          vectors holding names of all actors in each movie
 */
HashTable<string,vector<string>* >* buildHashTable(char movieFile[]) {
  HashTable<string,vector<string>* >* outHash = 
                                new HashTable<string,vector<string>* >;
  ifstream movies(movieFile);
  if (!movies.good()) {  // ensure input file is good
    throw std::runtime_error("buildHashTable in Oracle::input file is bad");
  }
  string actorMovieStr;
  getline(movies,actorMovieStr);
  while (!movies.eof()) {
    vector<string> actorMovieVect = split(actorMovieStr,'\t');
    string actorName = actorMovieVect[0] + " " + actorMovieVect[1];
    //cout << actorMovieStr << endl;
    string movieNameYear = actorMovieVect[2] + " " + actorMovieVect[3];
    //cout << "2" << endl;
    if (outHash->containsKey(movieNameYear)) { // update actor list
      outHash->get(movieNameYear)->push_back(actorName);
    } else {   // create pointer to vector holding actor, and add movie to table
      vector<string>* actors = new vector<string>;
      actors->push_back(actorName);
      outHash->put(movieNameYear,actors);
    }
    //cout << "3" << endl;
    getline(movies,actorMovieStr);
  }
  movies.close();
  return outHash;
}


/**
 * buildActorHash: builds a hastable of actor-pointer_to_actor key-value pair
 *
 * Inputs: Hashtable of movie-pointer_to_vector_of_actors key-value pair
 *
 * Returns: Hashtable with keys being actorname and values being pointers to 
 *          each actor name
 */
HashTable<string,string* >* 
        buildActorHash(HashTable<string,vector<string>* >* myHash) {
  HashTable<string,string* >* outHash = new HashTable<string,string*>;
  List<vector<string>* >* hashValues = myHash->getValues();  // list of movies
  while (!hashValues->isEmpty()) {
    vector<string>* movieActors = hashValues->removeHead();
    for (int i = 0; i < movieActors->size(); i++) {  // add all actors in movie
      string actor = (*movieActors)[i];
      string* actorP = new string(actor);
      outHash->put(actor,actorP);
    }
  }
  delete hashValues;
  return outHash;
}

/*----------------------------------------------------------------------------*/

/**
 * getRequest: gets uiser inputs to determine which query is run
 *
 * Inputs: integer representing nature of request: 0->initial request at launch
 *         of program; 2->after wrong input enterred; 1->other inputs
 * Returns: string of user input
 */
string getRequest(int when) {
  cout << endl;
  string userRequest;
  if (when == 0) {  // print only at the beginning of program launch
    cout << "\tWelcome to THE ORACLE OF BACON v1.0\n";
    cout << "type 5 or enter <CTRL-D> at any prompt to quit" << endl;
  }
  if (when == 0 || when == 1) {
    cout << "Make an INTEGER choice of what to do from the menu below:\n"; 
    cout << "\n1) Get all the movies a specific actor featured in.\n";
    cout << "2) Get the names of all actors in a movie.\n";
    cout << "3) Get the shortest movie path between two actors.\n";
    cout << "4) Get the average movie distance of an actor from other actors";
    cout << " in our database.\n";
    cout << "5) Quit.\n";
    cout << "\nYour Choice: ";
    getline(cin,userRequest);
    if (cin.eof()) {         // if user enters <ctrl-D> return a '5'
      userRequest = '5';
    }
  }
  if (when == 2) {   // if prior input was invalid
    cout << "Wrong Input, try again...: ";
    getline(cin,userRequest);
  }
  return userRequest;
}



/**
 * split:
 *
 * Inputs:   line, a string
 *           delim, a character to use as a delimiter to split the line
 * Returns:  a vector of whitespace-separated tokens in line
 */
vector<string> split(string line, char delim) {
  stringstream stream;  // Constructs an input stream from a string.
  stream << line;       // Put line into string stream.

  vector<string> allWords;
  string word;
  while (getline(stream, word, delim)){
    allWords.push_back(word);
  }
  return allWords;
}


/**
 * usage:  Prints an error message describing the use of this program.
 *
 * Inputs:  argv: the array of arguments passed to the program on the
 *                commandline.
 * Returns: nothing.
 */
void usage(char** argv) {
  cerr << "Usage: " << argv[0] << " <movie-file>\n";
  cerr << "Required options:\n";
  cerr << "  <movie-file>:     a movie file to generate the database\n";
}

