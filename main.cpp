#include <iostream>
#include <cstdint>
#include "SlidingTile.h"
#include "BFS.h"

int main(int argc, char* argv[]) {
	
	//pdb_a
	std::cout << "PDB_A:" << std::endl;
	std::vector<int> pattern_a = {0, 1, 4, 5};
	SlidingTile puzzle16_a;
	BFS bfsearch_a;
	bfsearch_a.BFS_pdb(pattern_a, "pdb_a.txt");

	//pdb_b
	std::cout << "PDB_B:" << std::endl;
	std::vector<int> pattern_b = { 0, 2, 3, 6, 7 };
	SlidingTile puzzle16_b;
	BFS bfsearch_b;
	bfsearch_b.BFS_pdb(pattern_b, "pdb_b.txt");

	//pdb_c
	std::cout << "PDB_C:" << std::endl;
	std::vector<int> pattern_c = { 0, 8, 9, 12, 13 };
	SlidingTile puzzle16_c;
	BFS bfsearch_c;
	bfsearch_c.BFS_pdb(pattern_c, "pdb_c.txt");

	//pdb_d
	std::cout << "PDB_D:" << std::endl;
	std::vector<int> pattern_d = { 0, 10, 11, 14, 15 };
	SlidingTile puzzle16_d;
	BFS bfsearch_d;
	bfsearch_d.BFS_pdb(pattern_d, "pdb_d.txt");

	//pdb_e
	std::cout << "PDB_E:" << std::endl;
	std::vector<int> pattern_e = { 0, 1, 2, 3, 4, 5, 6, 7 };
	SlidingTile puzzle16_e;
	BFS bfsearch_e;
	bfsearch_e.BFS_pdb(pattern_e, "pdb_e.txt");

	//hold output open
	std::getchar();
	return 0;
}