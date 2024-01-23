link: main.o factorizations.o trie_node_utils.o utils.o
	g++ main.o factorizations.o trie_node_utils.o utils.o -o suffix_array.exe -pg

main.o:
	g++ -c main.cpp -pg

factorizations.o:
	g++ -c factorizations.cpp -pg

trie_node_utils.o:
	g++ -c trie_node_utils.cpp -pg

utils.o:
	g++ -c utils.cpp -pg

clean:
	rm -rf *.o *.exe *.out report.txt report_graph.txt brief_report_with_call_graph.txt