#pragma once
#include <iostream>
//this holds the index of a code block in a htky file
//code block is determined by a curly bracket pair {} that is not in a string, comment, hotkey, etc...
struct TextBlock {
	//start and end are the line where the code block ends and begins from the brackets
	//substart and subend are where in the line the brackets are
	int start, end;

	friend std::ostream& operator<<(std::ostream& out, const TextBlock& c) {
		out << "[start = " << c.start << ", end = " << c.end << "]";
		return out;
	}
	bool operator<(const TextBlock& c) const {
		return start < c.start;
	}
};