#include		"../src/pepe_miner.h"
#include	<fstream>


enum Suit {club=0, diamond=1, heart=2, spade=3};
class Card{
public:
	int rank;
	Suit suit;
	Card(int rank_, Suit suit_);
	Card();
	string ascii();
	int compare(Card other);
private:
	string rank_str();
};
Card::Card(int rank_, Suit suit_){
	suit = suit_;
	rank = rank_;
}
Card::Card(){
	suit = club;
	rank = -1;
}

string Card::rank_str(){
	string temp;
	if (rank > 1 and rank < 10){
		temp = to_string(rank) + " ";
	} else {
		switch(rank){
			case 10:
				temp = "10";break;
			case 11:
				temp = "J ";break;
			case 12:
				temp = "Q ";break;
			case 13:
				temp = "K ";break;
			case 1:
				temp = "A ";break;
		}
	}
	return temp;
}

/*
 * cards sorted by number low -> high first and then by suit in order of clubs < diamonds < hearts < spades
 * returns 1 if other higher than self 0 if same cards and -1 otherwise
 */
int Card::compare(Card other){
	if (other.rank > rank){
		return 1;
	} else if (other.rank < rank){
		return -1;
	} else if (other.suit > suit){
		return 1;
	} else if (other.suit < suit){
		return -1;
	} else {
		return 0;
	}
}

/*
 * returns ascii representation of card
 */
string Card::ascii(){
	string rep = "", temp = "", check;
	ifstream card("cards.txt");

	switch(suit){
		case spade:
			check = "S:";
			break;
		case diamond:
			check = "D:";
			break;
		case heart:
			check = "H:";
			break;
		case club:
			check =  "C:";
			break;
	}
	while (temp.compare(check) != 0){
		card >> temp;
	}
	getline(card, temp);
	getline(card, temp);
	rep += temp;
	getline(card, temp);
	temp = temp.replace(1, 2, rank_str());
	rep += "\n" + temp;
	int i;
	for (i = 0; i < 4; i++){
		getline(card, temp);
		rep += "\n" + temp;
	}
	return rep;
}

/*
 * returns the value of the hand in poker. A hand with a greater score is always worth more than a hand with a lower score
 *
 * TODO
 	continue work and make sure you fix current functions to account for ace being either high or low
 */
int poker_value(Card hand[], int size){
	const int straight_flush = 8 *14;
	const int kind_4 = 7 * 14;
	const int full_house = 6 * 14;
	const int flush = 5 * 14;
	const int straight = 4 * 14;
	const int kind_3 = 3 * 14;
	const int pair_2 = 2 * 14;
	const int kind_2 = 1 * 14;

	int i, j, k, value = 0;
	Card temp;
//Sort hand
	for (i = 0; i < size; i++){
		for (j = i+1; j < size; j++){
			if (hand[i].compare(hand[j]) < 0){
				temp = hand[i];
				hand[i] = hand[j];
				hand[j] = temp;
			}
		}
	}

//straight flush
	int count = 1;
	for (k = club; k <= spade; k++){
		for (i = 0; i < size-1; i++){
			if (hand[i].rank + 1 == hand[i+1].rank and hand[i].suit == k and hand[i+1].suit == k){
			} else if (hand[i].rank == hand[i+1].rank){
				count = count;
			} else {
				count = 1;
			}
			if (count >= 5){
				value = max(value, hand[i+1].rank + straight_flush);
			}
		}
	}

//straight
	count = 1;
	for (i = 0; i < size-1; i++){
		if (hand[i].rank + 1 == hand[i+1].rank){
			count++;
		} else if (hand[i].rank == hand[i+1].rank){
			count = count;
		} else {
			count = 1;
		}
		if (count >= 5){
			value = max(value, hand[i+1].rank + straight);
		}
	}

//n of a kind, full house
	int full_3 = -1;
	count = 1;
	for (i = size - 1; i > 0; i--){
		count = 1;
		for (j = i-1; j >= 0; j--){
			if (hand[i].rank == hand[j].rank){
				count++;
			}
		}
		if (count == 2){
			if (full_3 > 0 and full_3 != hand[i+1].rank){
				value = max(value, full_3 + full_house);
			}
			value = max(value, hand[i+1].rank + kind_2);
		}
		if (count == 3){
			full_3 = hand[i+1].rank;
			value = max(value, hand[i+1].rank + kind_3);
		}
		if (count >= 4){
			value = max(value, hand[i+1].rank + kind_4);
		}
	}

//High card
	value = max(value, hand[size - 1].rank);


	return value;
}

Card cin_card(Card &new_c){
	int rank;
	Suit suit;
	string input;
	cin >> rank;
	cin >> input;
	if (input.compare("heart") == 0){
		suit = heart;
	} else if (input.compare("diamond") == 0){
		suit = diamond;
	} else if (input.compare("club") == 0){
		suit = club;
	} else if (input.compare("spade") == 0){
		suit = spade;
	} else {
		return new_c;
	}
	new_c.rank = rank;
	new_c.suit = suit;
	return new_c;
}

int main(int argc, char ** argv){

	Card temp_c;
	Card hand[5];
	int i;
	for (i = 0; i < 5; i++){
		cin_card(temp_c);
		hand[i] = temp_c;
	}
	cout << "Score: " << 
/*
	Card new_c;
	cin_card(new_c);
	Card hand[2];
	hand[0] = new_c;
	cin_card(new_c);
	hand[1] = new_c;
	int i;
	for (i = 0; i < 2; i++){
		cout << hand[i].ascii() << endl;
	}

	cout << "enter second hand: " << endl;
	Card hand2[2];
	cin_card(new_c);
	hand2[0] = new_c;
	cin_card(new_c);
	hand2[1] = new_c;

	int relative = poker_value(hand, 2) - poker_value(hand2, 2);
	cout << "hand 1: " << poker_value(hand, 2) << endl;
	cout << "hand 2: " << poker_value(hand2, 2);



	if (relative > 0){
		cout << "First hand better\n";
	} else if (relative == 0){
		cout << "Both hands equal\n";
	} else {
		cout << "Second hand better\n";
	}
*/

}