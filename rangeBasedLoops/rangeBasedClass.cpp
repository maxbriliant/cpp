#include <iostream>
#include <vector>
using std::vector, std::cout, std::endl;

class RangeBasedForClass{

	int start_;
	int end_;

public:	
	
	class Iterator{
		int current_value_;
		public:
		  Iterator(int value) : current_value_(value) {}


			int operator*() const {
				return current_value_;
			}

			// Präfix-Inkrementoperator
        	Iterator& operator++() {
	            current_value_++;
	            return *this;
	        }


	        // Postfix-Inkrementoperator (optional, aber gut zu haben)
	        Iterator operator++(int) {
	            Iterator temp = *this;
	            ++(*this); // Ruft den Präfix-Operator auf
	            return temp;
	        }
	    	// 	Ungleich-Operator (zum Vergleich mit dem End-Iterator)
	        bool operator!=(const Iterator& other) const {
	            return current_value_ != other.current_value_;
	        }

	        // Gleich-Operator (optional, aber nützlich)
	        bool operator==(const Iterator& other) const {
	             return !(*this != other); // Basiert auf dem Ungleich-Operator
	        }
};


	RangeBasedForClass(int s, int e) : start_{s}, end_{e} { }

	// begin() und end() Methoden der RangeBasedForClass
    Iterator begin() const {
        return Iterator(start_);
    }

    Iterator end() const {
        return Iterator(end_); // End-Iterator zeigt AUF den Wert NACH dem letzten gewünschten Wert
    }

};
