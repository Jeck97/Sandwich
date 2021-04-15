#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#define MAIN 5 //DIY menu types: BREAD, PATTY, VEGGIE, ADD-ON, DRINK
#define SUB 3 //each maximum choose of DIY menu types
#define setMENU 2 //SET menu types: SET, DRINK
#define EXIT 10 //constant that use for terminating the loop
using namespace std;

void selectDIY(int&, int&, int&);
void selectSET(int[]);
void calclulation(char, int&, int[], int, double&);
void printReceipt(int&, char&, int[][SUB], int[]);

int quantity, counter, i, j, DIY[MAIN][SUB], SET[setMENU];
double sum;
char menu, decision;

int main()
{
	cout << "Welcome to S2G1 SANDWICH !!!\n";
	cout << "How many meal do you want to order? (Enter '0' to cancel order) : ";
	cin >> quantity;
	while (quantity < 0 || cin.fail()) //loop when input is invalid
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\a\tInvalid input! Please enter again.\n";
		cout << "How many set do you want to order? (Enter '0' to cancel order) : ";
		cin >> quantity;
	}
	if (quantity == 0) //go to print when the order cancelled
		goto PRINT;

	while (counter < quantity) //*while loop* is used to loop until counter is equal to the number of meal that user entered
	{
		cout << "\nDo you want to order in DIY(D) or SET(S) ? ";
		cin >> menu;
		while (menu != 'D' && menu != 'd' && menu != 'S' && menu != 's') //loop when input is invalid
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\a\tInvalid input! Please enter again.\n";
			cout << "\nDo you want to order in DIY(D) or SET(S) ? ";
			cin >> menu;
		}
		if (menu == 'D' || menu == 'd') // *if-else if selection* is used to select the function of the menu
		{
			for (i = 0; i < MAIN; i++)
				for (j = 0; j < SUB; j++)
					selectDIY(i, j, DIY[i][j]); // *2D-array passed individually* by using two *for-loop* with thier counter i and j by the *pass by reference* to the selectDIY() function
		}
		else if (menu == 'S' || menu == 's')
			selectSET(SET);  // *1D-array passed whole* to the selectSET() function
		for (i = 0; i < MAIN; i++)
			calclulation(menu, i, DIY[i], SET[0], sum); // *2D-array passed row* and *1D-array passed individually* with the menu by the *pass by value* to the calclulation() function
	PRINT:
		printReceipt(quantity, decision, DIY, SET); // *2D-array and 1D-array pass whole* to the printReceipt() function
		counter++;
	}
	system("pause");
	return 0;
} //program end

void selectDIY(int& i, int& j, int& DIY)
{
	switch (i) // this i using in the *switch-case selection* is counter of the for-loop at the calling function
	{
	case 0: //select bread
		cout << "1: Normal\t\tRM1.00\n2: Multi-grain\t\tRM2.00\n3: Roasted\t\tRM2.00\n0: Cancel this order\n";
		cout << "\tPlease choose your bread (max1) : ";
		cin >> DIY;
		while (DIY < 0 || DIY > 3 || cin.fail()) //loop when input is invalid 
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\a\t\tInvalid input! Please enter again.\n";
			cout << "\tPlease choose your bread (max1) : ";
			cin >> DIY;
		}
		if (DIY == 0) //*if selection* is use to cancel this order when the user inputs 0
		{
			cout << "\aThis order is cancelled.\n";
			if (counter != quantity - 1)
				cout << "\tPlease continuous your next order\n";
			i = EXIT; //exit from i loop
		}
		j = EXIT; //exit from j loop to ensure that BREAD is only been select once (DIY[0][1] and DIY[0][2] will default to 0)
		break;
	case 1: //select patty
		if (j == 0) //let this menu only print once when j==0
			cout << "1: Egg\t\t\tRM1.00\n2: Roasted Chicken\tRM2.50\n3: Tempura Shrimp\tRM3.00\n0: Don't want\n";
		cout << "\tPlease choose your patty (max" << 3 - j << "): ";
		cin >> DIY;
		while (DIY < 0 || DIY > 3 || cin.fail()) //loop when input is invalid 
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\a\t\tInvalid input! Please enter again.\n";
			cout << "\tPlease choose your patty (max" << 3 - j << "): ";
			cin >> DIY;
		}
		if (DIY == 0)
			j = EXIT; //exit from j loop when users input 0 and continuous to next i loop
		else if (j != SUB - 1) //asking user to do decision if user does not input 0 
		{
			cout << "\t\tDo you want to add on patty? Y or N : ";
			cin >> decision;
			if (decision == 'N' || decision == 'n')
				j = EXIT; //exit from j loop when users input 'N' or 'n' and continuous to next i loop
		}
		break;
	case 2: //select veggie
		if (j == 0) //let this menu only print once when j == 0
			cout << "[All veggies are FREE]\n1: Tomatoes\n2: Lettuce\n3: Red Onions\n0: Don't want\n";
		cout << "\tPlease choose your veggies (max" << 3 - j << "): ";
		cin >> DIY;
		while (DIY < 0 || DIY > 3 || cin.fail()) //loop when input is invalid 
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\a\t\tInvalid input! Please enter again.\n";
			cout << "\tPlease choose your veggies (max" << 3 - j << "): ";
			cin >> DIY;
		}
		if (DIY == 0)
			j = EXIT; //exit from j loop when users input 0 and continuous to next i loop
		else if (j != SUB - 1) //asking user to do decision if user does not input 0 
		{
			cout << "\t\tDo you want to add on veggie? Y or N : ";
			cin >> decision;
			if (decision == 'N' || decision == 'n')
				j = EXIT; //exit from j loop when users input 'N' or 'n' and continuous to next i loop
		}
		break;
	case 3: //select extra
		if (j == 0) //let this menu only print once when j == 0
			cout << "[All extra add-on are FREE]\n1: Cheese\n2: Mayonnaise\n3: Chili sauce\n0: Don't want\n";
		cout << "\tPlease choose your extra add-on (max" << 3 - j << "): ";
		cin >> DIY;
		while (DIY < 0 || DIY > 3 || cin.fail()) //loop when input is invalid 
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\a\t\tInvalid input! Please enter again.\n";
			cout << "\tPlease choose your extra add-on (max" << 3 - j << "): ";
			cin >> DIY;
		}
		if (DIY == 0)
			j = EXIT; //exit from j loop when users input 0 and continuous to next i loop
		else if (j != SUB - 1) //asking user to do decision if user does not input 0 
		{
			cout << "\t\tDo you want to add on again? Y or N : ";
			cin >> decision;
			if (decision == 'N' || decision == 'n')
				j = EXIT; //exit from j loop when users input 'N' or 'n' and continuous to next i loop
		}
		break;
	case 4: //select drink
		cout << "1: Tea\t\t\tRM1.00\n2: Soft drink\t\tRM1.50\n3: Juice\t\tRM2.00\n0: Don't want\n";
		cout << "\tPlease choose your drink (max1) : ";
		cin >> DIY;
		while (DIY < 0 || DIY > 3 || cin.fail()) //loop when input is invalid
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\a\t\tInvalid input! Please enter again.\n";
			cout << "\tPlease choose your drink (max1) : ";
			cin >> DIY;
		}
		j = EXIT; //exit from j loop to ensure that DRINK is only been select once (DIY[4][1] and DIY[4][2] will default to 0)
		break;
	}//return to calling function and continuous j looping until j<SUB
}//after finishing j looping continuous i looping and then countinuous again new j looping until i<MAIN then proceed to calculation

void selectSET(int SET[])
{
	cout << "[BUY 1 set FREE 1 drink]\n1: Classic\t\tRM3.00\n2: Triple Cheese\tRM5.00\n3: VegeMax\t\tRM2.00\n4: Big MAC\t\tRM7.00\n0: Cancel this order\n";
	cout << "\tPlease choose your set : ";
	cin >> SET[0];
	while (SET[0] < 0 || SET[0] > 4 || cin.fail()) //loop when input is invalid
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\a\t\tInvalid input! Please enter again.\n";
		cout << "\tPlease choose your set : ";
		cin >> SET[0];
	}
	if (SET[0] != 0) //*if-else selection* is use to let user selects the DRINK if user does not input 0
	{
		cout << "1: Tea\n2: Soft drink\n3: Juice\n0: Don't want\n";
		cout << "\tPlease choose your drink : ";
		cin >> SET[1];
		while (SET[1] < 0 || SET[1] > 3 || cin.fail()) //loop when input is invalid
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\a\t\tInvalid input! Please enter again.\n";
			cout << "\tPlease choose your drink : ";
			cin >> SET[1];
		}
	}
	else //else this cancel and proceed to calclulation
	{
		cout << "\aThis order is cancelled.\n";
		if (counter != quantity - 1)
			cout << "\tPlease continuous your next order\n";
	}
}

void calclulation(char menu, int& i, int DIY[], int SET, double& sum)
{
	double x, priceDIY[9], priceSET[4];
	ifstream inputFile1("Price.txt"); //*input file* is use to get the price from Price.txt for calculation
	for (int k = 0; inputFile1 >> x; k++) //the loop will terminate when all of the price read into x
	{
		if (k < 9)
			priceDIY[k] = x; //first 9 values of x store into array priceDIY for each looping
		else
			priceSET[k - 9] = x; //remaining value in x is store into array priceSET until the loop finish
	}

	if (menu == 'D' || menu == 'd') //enter this part to calculate the price of DIY if user selected 'D' or 'd' at the previous function
	{
		for (j = 0; j < SUB; j++)
		{
			switch (i)
			{
			case 0: //for calculating the price of BREAD selected
				if (DIY[j] == 1) sum += priceDIY[0]; //*if selection* is used to add the price into sum for the corresponding BREAD selected
				if (DIY[j] == 2) sum += priceDIY[1];
				if (DIY[j] == 3) sum += priceDIY[2];
				break;
			case 1: //for calculating the price of PATTY selected
				if (DIY[j] == 1) sum += priceDIY[3]; //*if selection* is used to add the price into sum for the corresponding PATTY selected
				if (DIY[j] == 2) sum += priceDIY[4];
				if (DIY[j] == 3) sum += priceDIY[5];
				break;
			case 4: //for calculating the price of DRINK selected
				if (DIY[j] == 1) sum += priceDIY[6]; //*if selection* is used to add the price into sum for the corresponding DRINK selected
				if (DIY[j] == 2) sum += priceDIY[7];
				if (DIY[j] == 3) sum += priceDIY[8];
				break;
			default: //if user select 0, proceed to the next j loop until j<SUB
				break;
			}
		} //after finishing j looping return to the calling function and continuous i looping and then countinuous again new j looping until i < MAIN
	}//after finishing i looping then proceed to printReceipt
	else if (menu == 'S' || menu == 's') //enter this part to calculate the price of SET if user selected 'S' or 's' at the previous function
	{
		do //*do-while loop* is used to determine the selection of SET and add its price into sum
		{
			if (SET == (i + 1)) //for example, if i=0, then price[0](price of 1st SET) will add to sum when the user selected 1st SET because SET==(i+1)==(0+1)==1
				sum += priceSET[i];
			i++; //if not the i will +1 and loop for compairing 
		} while (i < 4); //loop will terminate if i==4 (menu of SET only has 4 types)
		i = EXIT; //exit from i loop after the do-while loop to proceed to printReceipt
	}
}

void printReceipt(int& quantity, char& decision, int DIY[][SUB], int SET[])
{
	int x = 1, qty1, qty2, qty3, add_on;
	double UnitPrice[15], Price2[7], TotalPrice1, TotalPrice2, TotalPrice3, MealPrice = 0;
	string item1[15], item2[7];

	ifstream inputFile2("DIYPrice.txt"); //get the item name and corresponding price from DIYPrice.txt for printing receipt
	for (i = 0; i < 15; i++)
		inputFile2 >> item1[i] >> UnitPrice[i]; //store 15 item names into string array and their corresponding prices into double array
	ifstream inputFile3("SETPrice.txt"); //get the item name and corresponding price from SETPrice.txt for printing receipt
	for (i = 0; i < 7; i++)
		inputFile3 >> item2[i] >> Price2[i]; //store 7 item names into string array and their corresponding prices into double array

	ofstream outputFile; //declare the output file prepare for using
	if (counter == 0)
		outputFile.open("Receipt.txt", ios::out); //the data store in the Receipt.txt will overwrite for the first selected meal
	else
		outputFile.open("Receipt.txt", ios::out | ios::app); //the data store in the Receipt.txt will not overwrite (continuously) from the second selected meal and so on

	if (quantity != 0) //if user does not cancel the order
	{
		if (counter == 0) //print out the heading once
		{
			outputFile << "\t\t\t\t\t\t\t\t**** RECEIPT ****\n\n";
			outputFile << setw(2) << "NUM" << setw(25) << "ITEMS" << setw(20) << "UNIT PRICE (RM)" << setw(8) << "QTY" << setw(20) << "TOTAL PRICE (RM)" << endl << endl;
		}
		if (menu == 'D' || menu == 'd') //enter this part to print the receipt of DIY if user selected 'D' or 'd' at the previous function
		{
			outputFile << "*MEAL " << counter + 1 << "-DIY*" << endl;
			for (i = 0; (i < MAIN && DIY[0][0] != 0); i++)
			{
				for (j = 0; j < SUB; j++)
				{
					switch (i)
					{
					case 0: //print out about BREAD
						switch (DIY[i][j]) //print the receipt for selected BREAD and add its price into MealPrice
						{
						case 1: outputFile << setw(2) << x << setw(25) << item1[0] << setw(20) << fixed << setprecision(2) << UnitPrice[0] << setw(8) << "1" << setw(20) << UnitPrice[0] << endl; MealPrice += UnitPrice[0]; x++; break;
						case 2: outputFile << setw(2) << x << setw(25) << item1[1] << setw(20) << fixed << setprecision(2) << UnitPrice[1] << setw(8) << "1" << setw(20) << UnitPrice[1] << endl; MealPrice += UnitPrice[1]; x++; break;
						case 3: outputFile << setw(2) << x << setw(25) << item1[2] << setw(20) << fixed << setprecision(2) << UnitPrice[2] << setw(8) << "1" << setw(20) << UnitPrice[2] << endl; MealPrice += UnitPrice[2]; x++; break;
						} break;
					case 1: //print out about PATTY
						if (j == 0) //initialize the value at the start of this j looping
						{
							qty1 = 0; qty2 = 0; qty3 = 0;
							TotalPrice1 = 0; TotalPrice2 = 0; TotalPrice3 = 0;
						}
						switch (DIY[i][j])
						{
						case 1: qty1++; TotalPrice1 += UnitPrice[3]; break; //quantity and price will be added if the corresponding PATTY is selected
						case 2: qty2++; TotalPrice2 += UnitPrice[4]; break;
						case 3: qty3++; TotalPrice3 += UnitPrice[5]; break;
						}
						if (j == 2 && (DIY[i][0] == 1 || DIY[i][1] == 1 || DIY[i][2] == 1)) //print the receipt for egg at the end of this j looping if at least 1 time egg is seleced
						{
							outputFile << setw(2) << x << setw(25) << item1[3] << setw(20) << fixed << setprecision(2) << UnitPrice[3] << setw(8) << qty1 << setw(20) << TotalPrice1 << endl;
							MealPrice += TotalPrice1; //the total price of egg selected will be added into MealPrice
							x++;
						}
						if (j == 2 && (DIY[i][0] == 2 || DIY[i][1] == 2 || DIY[i][2] == 2)) //print the receipt for Roasted_Chicken at the end of this j looping if at least 1 time Roasted_Chicken is seleced
						{
							outputFile << setw(2) << x << setw(25) << item1[4] << setw(20) << fixed << setprecision(2) << UnitPrice[4] << setw(8) << qty2 << setw(20) << TotalPrice2 << endl;
							MealPrice += TotalPrice2; //the total price of Roasted_Chicken selected will be added into MealPrice
							x++;
						}
						if (j == 2 && (DIY[i][0] == 3 || DIY[i][1] == 3 || DIY[i][2] == 3)) //print the receipt for Tempura_Shrimp at the end of this j looping if at least 1 time Tempura_Shrimp is seleced
						{
							outputFile << setw(2) << x << setw(25) << item1[5] << setw(20) << fixed << setprecision(2) << UnitPrice[5] << setw(8) << qty3 << setw(20) << TotalPrice3 << endl;
							MealPrice += TotalPrice3; //the total price of Tempura_Shrimp selected will be added into MealPrice
							x++;
						}
						break;
					case 2: //print out about VEGGIE
						if (j == 0) //initialize the value at the start of this j looping
						{
							qty1 = 0; qty2 = 0; qty3 = 0;
						}
						switch (DIY[i][j])
						{
						case 1: qty1++; break; //quantity will be added if the corresponding VEGGIE is selected
						case 2: qty2++; break;
						case 3: qty3++; break;
						}
						if (j == 2 && (DIY[i][0] == 1 || DIY[i][1] == 1 || DIY[i][2] == 1)) //print the receipt for Tomatoes at the end of this j looping if at least 1 time Tomatoes is seleced
						{
							outputFile << setw(2) << x << setw(25) << item1[6] << setw(20) << fixed << setprecision(2) << UnitPrice[6] << setw(8) << qty1 << setw(20) << UnitPrice[6] << endl;
							x++;
						}
						if (j == 2 && (DIY[i][0] == 2 || DIY[i][1] == 2 || DIY[i][2] == 2)) //print the receipt for Lettuce at the end of this j looping if at least 1 time Lettuce is seleced
						{
							outputFile << setw(2) << x << setw(25) << item1[7] << setw(20) << fixed << setprecision(2) << UnitPrice[7] << setw(8) << qty2 << setw(20) << UnitPrice[7] << endl;
							x++;
						}
						if (j == 2 && (DIY[i][0] == 3 || DIY[i][1] == 3 || DIY[i][2] == 3)) //print the receipt for Red_Onions at the end of this j looping if at least 1 time Red_Onions is seleced
						{
							outputFile << setw(2) << x << setw(25) << item1[8] << setw(20) << fixed << setprecision(2) << UnitPrice[8] << setw(8) << qty3 << setw(20) << UnitPrice[8] << endl;
							x++;
						}
						break;
					case 3: //print out about ADD-ON
						if (j == 0) //initialize the value at the start of this j looping
						{
							qty1 = 0; qty2 = 0; qty3 = 0;
						}
						switch (DIY[i][j])
						{
						case 1: qty1++; break; //quantity will be added if the corresponding ADD-ON is selected
						case 2: qty2++; break;
						case 3: qty3++; break;
						}
						if (j == 2 && (DIY[i][0] == 1 || DIY[i][1] == 1 || DIY[i][2] == 1)) //print the receipt for Cheese at the end of this j looping if at least 1 time Cheese is seleced
						{
							outputFile << setw(2) << x << setw(25) << item1[9] << setw(20) << fixed << setprecision(2) << UnitPrice[9] << setw(8) << qty1 << setw(20) << UnitPrice[9] << endl;
							x++;
						}
						if (j == 2 && (DIY[i][0] == 2 || DIY[i][1] == 2 || DIY[i][2] == 2)) //print the receipt for Mayonnaise at the end of this j looping if at least 1 time Mayonnaise is seleced
						{
							outputFile << setw(2) << x << setw(25) << item1[10] << setw(20) << fixed << setprecision(2) << UnitPrice[10] << setw(8) << qty2 << setw(20) << UnitPrice[10] << endl;
							x++;
						}
						if (j == 2 && (DIY[i][0] == 3 || DIY[i][1] == 3 || DIY[i][2] == 3)) //print the receipt for Chili_sauce at the end of this j looping if at least 1 time Chili_sauce is seleced
						{
							outputFile << setw(2) << x << setw(25) << item1[11] << setw(20) << fixed << setprecision(2) << UnitPrice[11] << setw(8) << qty3 << setw(20) << UnitPrice[11] << endl;
							x++;
						}
						break;
					case 4: //print out about DRINK
						switch (DIY[i][j]) //print the receipt for selected DRINK and add its price into MealPrice
						{
						case 1: outputFile << setw(2) << x << setw(25) << item1[12] << setw(20) << fixed << setprecision(2) << UnitPrice[12] << setw(8) << "1" << setw(20) << UnitPrice[12] << endl; MealPrice += UnitPrice[12]; x++; break;
						case 2: outputFile << setw(2) << x << setw(25) << item1[13] << setw(20) << fixed << setprecision(2) << UnitPrice[13] << setw(8) << "1" << setw(20) << UnitPrice[13] << endl; MealPrice += UnitPrice[13]; x++; break;
						case 3: outputFile << setw(2) << x << setw(25) << item1[14] << setw(20) << fixed << setprecision(2) << UnitPrice[14] << setw(8) << "1" << setw(20) << UnitPrice[14] << endl; MealPrice += UnitPrice[14]; x++; break;
						} break;
					}
				}
			}
			if (DIY[0][0] != 0) //print the MealPrice of this meal into receipt if the user does not cancel
			{
				outputFile << setw(65) << setfill('-') << "Price MEAL " << counter + 1 << ": RM " << fixed << setprecision(2) << MealPrice << endl;
				MealPrice = 0; //initialize the MealPrice to  0 for the next selection
				for (i = 0; i < MAIN; i++)
					for (j = 0; j < SUB; j++)
						DIY[i][j] = 0; //initialize the array DIY to 0 for the next selection
			}
			else //print "Order Cancelled" into receipt if user inputs 0 for this meal
				outputFile << setw(75) << setfill('-') << "Order Cancelled" << endl;
		}
		else if (menu == 'S' || menu == 's') //enter this part to print the receipt of SET if user selected 'S' or 's' at the previous function
		{
			outputFile << "*MEAL " << counter + 1 << "-SET*" << endl;
			for (int s = 0; (s < setMENU && SET[0] != 0); s++)
			{
				switch (s)
				{
				case 0: //print out about SET
					switch (SET[s]) //print the receipt for selected SET and add its price into MealPrice
					{
					case 1: outputFile << setw(2) << x << setw(25) << item2[0] << fixed << setprecision(2) << setw(28) << "1" << setw(20) << Price2[0] << endl; MealPrice += Price2[0]; x++; break;
					case 2: outputFile << setw(2) << x << setw(25) << item2[1] << fixed << setprecision(2) << setw(28) << "1" << setw(20) << Price2[1] << endl; MealPrice += Price2[1]; x++; break;
					case 3: outputFile << setw(2) << x << setw(25) << item2[2] << fixed << setprecision(2) << setw(28) << "1" << setw(20) << Price2[2] << endl; MealPrice += Price2[2]; x++; break;
					case 4: outputFile << setw(2) << x << setw(25) << item2[3] << fixed << setprecision(2) << setw(28) << "1" << setw(20) << Price2[3] << endl; MealPrice += Price2[3]; x++; break;
					} break;
				case 1: //print out about DRINK
					switch (SET[s]) //print the receipt for selected DRINK
					{
					case 1: outputFile << setw(2) << x << setw(25) << item2[4] << fixed << setprecision(2) << setw(28) << "1" << setw(20) << Price2[4] << endl; x++; break;
					case 2: outputFile << setw(2) << x << setw(25) << item2[5] << fixed << setprecision(2) << setw(28) << "1" << setw(20) << Price2[5] << endl; x++; break;
					case 3: outputFile << setw(2) << x << setw(25) << item2[6] << fixed << setprecision(2) << setw(28) << "1" << setw(20) << Price2[6] << endl; x++; break;
					} break;
				}
			}
			if (SET[0] != 0) //print the MealPrice of this meal into receipt if the user does not cancel
			{
				outputFile << setw(65) << setfill('-') << "Price MEAL " << counter + 1 << ": RM " << fixed << setprecision(2) << MealPrice << endl;
				MealPrice = 0; //initialize the MealPrice to  0 for the next selection
			}
			else //print "Order Cancelled" into receipt if user inputs 0 for this meal
				outputFile << setw(75) << setfill('-') << "Order Cancelled" << endl;
		}
		if (counter == quantity - 1) //asking user at the after the last selection of meal done
		{
			cout << "\nDo you want to add your order? Y or N : ";
			cin >> decision;
			if (decision == 'N' || decision == 'n') //if user input 'N' or 'n', print the sum for user and in the reciept
			{
			THANKS:
				cout << "\n\nThe total price for your order is RM " << fixed << setprecision(2) << sum << endl;
				cout << "_" << setw(26) << setfill('-') << "THANK YOU !!!" << setw(15) << setfill('-') << "_\n\n";
				outputFile << "\n-" << setw(40) << setfill('_') << "TOTAL Price: RM " << fixed << setprecision(2) << sum << setw(30) << setfill('_') << "-" << endl;
			}
			else //else let user input the quantity want to add on
			{
				cout << "\tHow many meal do you want to add-on? :";
				cin >> add_on;
				if (add_on == 0)
					goto THANKS;
				quantity += add_on;
			}
		}
	} //return to calling function
	else //print "Order CANCELLED" for user and in the receipt if user cancel the order
	{
		cout << "\a\nOrder Cancelled...\n";
		outputFile << setw(2) << "NUM" << setw(25) << "ITEMS" << setw(20) << "UNIT PRICE (RM)" << setw(8) << "QTY" << setw(20) << "TOTAL PRICE (RM)" << endl << endl;
		outputFile << "\n-" << setw(40) << setfill('_') << "Order CANCELLED" << setw(35) << setfill('_') << "-" << endl;
	} //return to calling function
}