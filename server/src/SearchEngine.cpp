#include "SearchEngine.h"

// Generates a new list of results based on the search term
// and returns the list
std::vector<struct SearchEngine::result> SearchEngine::search(std::string searchTerm) {
	
	// For now search results will be hard coded
	// Once dispersie works we can do the real deal
	
	return searchResults;
}

// Returns the current list of results
std::vector<struct SearchEngine::result> SearchEngine::getResults() {
	
	// For now search results will be hard coded
	// Once dispersie works we can do the real deal
	
	return searchResults;
}

// Returns the result with a certain filename
struct SearchEngine::result SearchEngine::getResultWithName(std::string filename){
	
	for(int i = 0; i < searchResults.size(); i++) {
		
		if(searchResults.at(i).filename.compare(filename) == 0){
			return searchResults.at(i);
		}
	}
	struct SearchEngine::result failed;
	failed.filename = "failed";
	failed.tracker = "failed";
	failed.hash = "failed";
	return failed;
}