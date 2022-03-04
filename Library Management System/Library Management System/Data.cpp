#include "Data.h"

book getDataList(const std::string& filename) {
	std::string base_path = ("./data/" + filename + ".txt");
	std::ifstream textfile;
	textfile.open(std::filesystem::path(base_path));
	book returnBook;
	std::string line;
	if (textfile.is_open()) {
		getline(textfile, line);
		if (!line.empty()) {
			book* entry = new book;
			entry->ISBN = filename;
			entry->title = line;
			getline(textfile, line);
			entry->author = line;
			getline(textfile, line);
			entry->publisher = line;
			getline(textfile, line);
			entry->genre = line;
			getline(textfile, line);
			entry->status = line;
			while (getline(textfile, line)) {
				if (line != "\n")
					entry->borrower_record.push_back(line);
			}
			if (entry->status == "Reserved") {
				entry->reserveName = entry->borrower_record.back();
				entry->borrower_record.pop_back();
			}
			if (!entry->title.empty() && !entry->author.empty() && !entry->publisher.empty() && !entry->genre.empty()) {
				returnBook = *entry;
			}
		}
	}
	return returnBook;
};

std::string base64_encode(const std::string& in) {
	const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out;

    int val = 0, valb = -6;
    
    for (char c : in) {
        val = (val << 8) + c;
        valb += 8;
        
        while (valb >= 0) {
            out.push_back(b[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    
    if (valb > -6)
        out.push_back(b[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4)
        out.push_back('=');
    
    return out;
}
