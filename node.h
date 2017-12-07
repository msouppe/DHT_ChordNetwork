/*
 *	Filename: node.h
 *	Author: Mariette Souppe
 */

#ifndef NODE_H_
#define NODE_H_
#include <iostream>
#include <stdint.h>
#include <map>
#include <set>
#include <vector>
#include <cmath>

#define BITLENGTH 3

using namespace std;

// Forward declaration
class Node;

// Since the index uniquely determines the interval,
// only the successor needs to be maintained.
class FingerTable{
	struct fingertable_data {
		int start;
		int interval[2];
		Node* success;
	};

	private:
		uint8_t nodeId_;
		vector<fingertable_data*> fingerTable_;

	public:
		FingerTable(uint8_t nodeId) {
			nodeId_ = nodeId;

			// According to Chord paper, the finger table starts from index=1
			fingerTable_.resize(BITLENGTH + 1);

			this->set_start(nodeId_);
			this->set_interval(nodeId_);
//			cout << "FingerTable Constructor" << endl;
		}

		// Init FingerTable set node's start value
		void set_start(uint8_t nodeId_);

		// Init FingerTable set node's interval
		void set_interval(uint8_t nodeId_);

		// Init FingerTable set node's successor
		void set_successor(size_t index, Node* successor);

		// Get start value in a FingerTable, return that value
		uint64_t getFingerTableData_start(size_t index);

		// Get node in a FingerTable, return that node
		Node* getFingerTableData_successor(size_t index);

		// TODO: Print out FingerTable nicely
		void prettyPrint();

		// note Node* was changed from uint8_t
		fingertable_data* get(size_t index) {
			return fingerTable_[index];
		}
};

class Node {
	private:
		uint64_t id_;
		FingerTable fingerTable_;
		map<uint8_t, uint8_t> localKeys_;

	public:
		Node(uint8_t id): id_(id), fingerTable_(id) {}

		// TODO: implement node join function
		void join(Node* node);

		void initNodesFingerTable(Node* node);

		// TODO: implement DHT lookup
		uint8_t find(uint8_t key);

		// TODO: implement DHT key insertion
		void insert(uint8_t key);

		// TODO: implement DHT key deletion
		void remove(uint8_t key);

		// Get node's Id
		int getId();

		// Get FingerTable
		FingerTable getFingerTable();

		// Update FingerTable
		void update_other_tables();

		// Ask node n to find id's successor
		Node* find_successor(uint64_t id_);

		// Ask node n to find id's predecessor
		Node* find_predecessor(uint64_t id_);

		// Return closest finger preceding id
		Node* closest_preceding_finger(uint64_t id_);

};

#endif /* NODE_H_ */
