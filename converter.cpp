#include "tinyxml.cpp"
#include "tinystr.cpp"
#include "tinyxmlerror.cpp" 
#include "tinyxmlparser.cpp"
#include "tinyxml.h"
#include "tinystr.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

int LCP(const std::vector<std::string> &a) {
	if (a.empty()) {
		return -1;
	}
	for (int len = 0; ; ++len) {
		for (const std::string &v : a) {
			if (len >= (int)v.size() || v[len] != a[0][len]) {
				return len;
			}
		}
	}
	return -1;
}

int LCS(const std::vector<std::string> &a) {
	auto t = a;
	for (std::string &v : t) {
		std::reverse(v.begin(), v.end());
	}
	return LCP(t);
}

int main() {
	std::ofstream fout("data.yml");

	TiXmlDocument prb;
	if (!prb.LoadFile(".prb")) {
		std::cout << "Failed to load file \".prb\"." << std::endl;
		return 0;
	}

	TiXmlElement *root = prb.FirstChildElement();
	if (root == NULL || root->ValueTStr() != "problem") {
		std::cout << "No subtasks." << std::endl;
		return 0;
	}

	std::vector<std::string> in, out;
	std::vector<std::vector<int>> id;
	std::vector<std::string> sc;
	for (TiXmlElement *dd = root->FirstChildElement(); dd != NULL; dd = dd->NextSiblingElement()) {
		if (dd->ValueTStr() != "task") {
			continue;
		}
		for (TiXmlElement *d = dd->FirstChildElement(); d != NULL; d = d->NextSiblingElement()) {
			if (d->ValueTStr() != "subtask") {
				continue;
			}
			std::string score = d->Attribute("score");
			sc.push_back(score);
			id.push_back({});
			for (TiXmlElement *c = d->FirstChildElement(); c != NULL; c = c->NextSiblingElement()) {
				if (c->ValueTStr() != "point") {
					continue;
				}
				id.back().push_back(in.size());
				in.push_back(c->Attribute("in"));
				out.push_back(c->Attribute("out"));
			}
		}
	}

	if (sc.empty()) {
		std::cout << "No subtasks." << std::endl;
		return 0;
	}
	if (in.empty()) {
		std::cout << "No test cases." << std::endl;
		return 0;
	}

	int inp = LCP(in), ins = LCS(in), inl = 1e9;
	int outp = LCP(out), outs = LCS(out), outl = 1e9;
	for (const std::string &v : in) {
		inl = std::min(inl, (int)v.size());
	}
	for (const std::string &v : out) {
		outl = std::min(outl, (int)v.size());
	}
	inp = std::min(inp, inl - 1), ins = std::min(ins, inl - 1 - inp);
	outp = std::min(outp, outl - 1), outs = std::min(outs, outl - 1 - outp);

	std::string inform = in[0].substr(0, inp) + "#" + in[0].substr((int)in[0].size() - ins, ins);
	std::string outform = out[0].substr(0, outp) + "#" + out[0].substr((int)out[0].size() - outs, outs);

	for (int i = 0; i < (int)in.size(); ++i) {
		in[i] = in[i].substr(inp, (int)in[i].size() - inp - ins);
		out[i] = out[i].substr(outp, (int)out[i].size() - outp - outs);
		if (in[i] != out[i]) {
			std::cout << "Cannot recognize the common part of the filename." << std::endl;
			return 0;
		}
	}

	fout << "subtasks: \n";
	for (int i = 0; i < (int)sc.size(); ++i) {
		fout << "  - score: " << sc[i] << "\n";
		fout << "    type: min\n";
		fout << "    cases: [";
		for (int j = 0; j < (int)id[i].size(); ++j) {
			if (j) {
				fout << ", ";
			}
			fout << "\'" << in[id[i][j]] << "\'";
		}
		fout << "]\n";
	}
	fout << "\n";
	fout << "inputFile: \'" << inform << "\'\n";
	fout << "outputFile: \'" << outform << "\'\n";
	std::cout << "Success." << std::endl;
	return 0;
}
