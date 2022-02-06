#include "Data.h"
using namespace std;
vector<string>searchDataFiles(string query) {
	string base_path = (filesystem::current_path().string() + "/data/");
	vector<string>filenamelist;
	for (const filesystem::directory_entry& textfiles : filesystem::directory_iterator(base_path)) {
		string filename = textfiles.path().filename().string();
		filename = filename.substr(0, filename.size() - 4);
		filenamelist.push_back(filename);
	}
	return filenamelist;
}
vector <book_indexing> getDataList(string filename) {
	std::string base_path = (filesystem::current_path().string() + "/data/" + filename + ".txt");
	std::ifstream textfile;
	textfile.open(filesystem::path(base_path));
	std::vector <book_indexing> dataList;
	std::string line;
	if (textfile.is_open()) {
		while (getline(textfile, line)) {
			if (!line.empty()) {
				if (line[0] == '+') {
					line = line.substr(1, line.size() - 1);
					book_indexing* entry = new book_indexing;
					entry->title = line;
					getline(textfile, line); 
					line = line.substr(1, line.size() - 1);
					entry->author = line;
					getline(textfile, line);
					line = line.substr(1, line.size() - 1);
					entry->publisher = line;
					getline(textfile, line);
					line = line.substr(1, line.size() - 1);
					entry->genre = line;
					//borrower's record not yet implemented
					if (!entry->title.empty()&&!entry->author.empty()&&!entry->publisher.empty()&&!entry->genre.empty()) {
						dataList.push_back(*entry);
					}
				}

			}
		}
	}
	return dataList;
}