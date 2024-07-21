#pragma once
#include <iostream>
//this holds the index of a code block in a htky file
//code block is determined by a curly bracket pair {} that is not in a string, comment, hotkey, etc...
struct CodeBlock {
	//start and end are the line where the code block ends and begins from the brackets
	//substart and subend are where in the line the brackets are
	int start, end;

	friend std::ostream& operator<<(std::ostream& out, const CodeBlock& c) {
		out << "[start = " << c.start << ", end = " << c.end << "]";
		return out;
	}
	bool operator<(const CodeBlock& c) const {
		return start < c.start;
	}
};