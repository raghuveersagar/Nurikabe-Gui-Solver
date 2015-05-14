#include"puzzle.h"
#include<stack>
#include<iostream>
using namespace std;

template<class T>
T PuzzleSolver<T>::solve() {
	
	stack<Node<T>*> queueOfConfigs;
	queueOfConfigs.push(startNode);
	Node<T>* finalNode = 0;
	bool breakAll = false;
	
	int i = 0;
	while (!queueOfConfigs.empty()) {
		Node<T>* temp = queueOfConfigs.top();
		if (isRequiredConfiguration(temp->nodeData)) {

			

            //printFinalConfig(finalNode);

			breakAll = true;
			break;
		}
		//cout << "Popping from stack" << endl;
		//printFinalConfig(temp);
		
		//if (i == 10)
			//break;
		

		
		queueOfConfigs.pop();
        vector<Node<T>*> possibleConfigs;
                //getConfigurations(temp);
		//cout << "Adding entries to queue" << possibleConfigs.size()<<endl;

		for (typename vector<Node<T>*>::iterator it = possibleConfigs.begin();
			it != possibleConfigs.end(); it++) {
			if (isRequiredConfiguration((**it).nodeData)) {
				
				finalNode = *it;

                //printFinalConfig(finalNode);
				
				breakAll = true;
				break;
			}
			else {
				//cout << "Putting on stack" << endl;
				//printFinalConfig(*it);
				queueOfConfigs.push(*it);
			}

		}
		if (breakAll)
			break;

		i++;
	}
	
	if (!breakAll)
		cout << "No solutions" << endl;


    return finalNode->nodeData;
}
