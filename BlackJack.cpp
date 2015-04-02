// BlackJack

// A classic card game, man VS A.I.

// 4-1-2015

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring> 

using namespace std;

char Get_Option(char &s){
	char *string;
	string=new char(100);
	while (true){
		try{
			cin >> string; 
			if (strlen(string)!=1) throw(1);
			s=toupper(string[0]);
			if (s=='Y'||s=='N'){
				delete []string;
				return(s); }
			throw(s);	
		}
		catch(char){
			cout << "Error: Invalid Input.Please Input Again:";}
		catch(int){
			cout << "Error: Please input a SINGLE character again.  ";
		}
		
		
	}
}

void Distribute_Cards(bool cards[4][13],int *target){      // Distribute 1 card to the target's hand
	int color,number;
	while (true){
		color=rand()%4;
		number=rand()%13;
		if (!cards[color][number]){                        // If the card is still in the deck
			cards[color][number]=true;					   
			target[target[0]+1]=color*100+number;          // target[x]=ABB, A = color, BB = point.
			++target[0];
			break;
		}
	}
}

double Show_Cards(int *target){								// Show all the cards on the target's hand. Return the total score of all the cards.
	double sum=0;
	for (int i=1;i<=target[0];++i){
		switch (target[i]/100){
			case 0: cout<<"Heart ";break;
			case 1: cout<<"Spade ";break;
			case 2: cout<<"Diamond ";break;
			case 3: cout<<"Club ";break;
			default:cout<<"Error!!";}
		if (target[i]%100>9 or (target[i]%100 == 0))
			switch (target[i]%100){
				case 10: cout<<"J  ";sum+=0.5;break;
				case 0: cout<<"A  ";++sum;break;
				case 11: cout<<"Q  ";sum+=0.5;break;
				case 12: cout<<"K  ";sum+=0.5;break;
				default: cout<<"Error!!  ";break;}
		else{
			cout<< target[i]%100 + 1 << "  ";
			sum+= target[i]%100 +1;
			
		}
		
	}
	cout<<endl;
	return(sum);
}


int main(){
	bool cards[4][13]={0};   // the first indice stands for color; the second indice stands for point.
	int player[30]={0},computer[30]={0},i,j; //player[0] and computer[0] is the number of cards that player/computer has.
	double score_player,score_computer;
	char flag;
	srand(time(0));
	while (true){
		for (i=0;i<30;++i){
			player[i]=0;computer[i]=0;
		}
		for (i=0;i<4;++i)
			for (j=0;j<13;++j)
				cards[i][j]=false;
		score_player=0.0;score_computer=0.0;
		cout<<"Your Turn:"<<endl;
		Distribute_Cards(cards,player);
		Distribute_Cards(cards,player);
		cout<<"Your Cards: ";
		score_player=Show_Cards(player);
		while (score_player<=21){							// Loop until player explodes or don't asking for cards.
			cout<<"Do you want 1 more card?(Y/N)";
			Get_Option(flag);
			if (flag=='N') break;
			Distribute_Cards(cards,player);
			cout<<"Your Cards: ";
			score_player=Show_Cards(player);
		}
		cout << "Your Score:"<<score_player<<endl;
		if (score_player>21) cout <<"You Lose!"<<endl;
		else{												// Begin computer's turn.
			cout << "Computer's Turn:"<<endl;
			Distribute_Cards(cards,computer);
			Distribute_Cards(cards,computer);
			cout<<"Computer's Cards: ";
			score_computer=Show_Cards(computer);
			while (score_computer<=21
					&&(score_computer<=score_player
					||((score_computer==score_player) 
					&& (computer[0]<=player[0])))){		    // Drawing cards until computer wins.
				Distribute_Cards(cards,computer);
				cout<<"Computer's Cards: ";
				score_computer=Show_Cards(computer);}
			if (score_computer>21) 
					cout <<"Computer's Score: "<<score_computer<<endl<<"You Win!"<<endl;
			else if (score_computer==score_player && computer[0]==player[0])
					cout <<"Computer's Score: "<<score_computer<<endl<<"Draw..."<<endl;
				else cout << "Computer's Score: "<<score_computer<<endl<<"You Lose!"<<endl;
		}
		cout << "Wanna play for another round?(Y/N)";
		if (Get_Option(flag) =='N') break;
	}
}
// --The Sign Painter
