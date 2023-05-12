#include <iostream>
#include <string>
#include <iomanip> //setw

class TennisMatch{

    private: 

    // Private Variables
    int score1= 0; int score2 = 0; int games1 = 0; int games2 = 0; //points and games
    int server = 1; //This keeps track of server (either 1 or 2)
    std::string player1, player2;
    bool running = true;
    int gameWinner = 0;
    
    
    // Functions
    void addScoreToWinner(){ //Takes and input and adds the points to the round winner.
        int lastWinner;
        std::cout << "\n";
        std::cout << "Input winner: ";
        std::cin >> lastWinner;
        std::cout << "\n" << std::endl;

        if (lastWinner==1){
            score1++;
        }
        if (lastWinner==2){
            score2++;
        }
    }
    
    void announcement(){ // Umpire Annouces in "english" rather than scores.

        std::cout << " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
        if (gameWinner == 1){
            std::cout << "Umpire : game, " << player1 <<std::endl;
            gameWinner = 0;
        } 
        if (gameWinner==2){
            std::cout << "Umpire : game, " << player2 <<std::endl;
            gameWinner = 0;
        } 
        
        //Non server reliant annoucments
        if (score1==0 && score2==0){
            std::cout << "Umpire: " << "love-all" << std::endl;
        }
        if (score1==1 && score2==1){
            std::cout << "Umpire: " << "fifteen-all" << std::endl;
        }
        if (score1==2 && score2==2){
            std::cout << "Umpire: " << "thirty-all" << std::endl;
        }
        if ((score1>=3 && score2>=3) && (score1 == score2)){
            std::cout << "Umpire: " << "deuce" << std::endl;
        }

        //Server reliant annoucements
        if (((score1 < 4 && score2 < 3) && (score1 != score2)) || ((score1 < 3 && score2 < 4) && (score1 != score2)) ){//Both less than 40
            if (server==1){
                std::cout << "Umpire: " << intToSpeach(score1, 1) << " - " << intToSpeach(score2, 2) << std::endl;
            }
            if (server==2){
                std::cout << "Umpire: " << intToSpeach(score2, 2) << " - " << intToSpeach(score1, 1) << std::endl;
            }
        }

        if (score1>=3 && score2>=3){
            if ((score1 == score2 + 1)){
            
                std::cout << "Umpire: " << "Advantage " << player1 << std::endl;
            }
            
            if ((score2 == score1 + 1)){
                
                std::cout << "Umpire: " << "Advantage " << player2 <<  std::endl;
            }
        }
        std::cout << std::endl;
    }


    void scoreReading(){ //Prints out the scoreboard.
        std::cout << std::setw(19) << player1 << serving(1) << " | " << serving(2) << player2;  //Server
        std::cout << std::endl << std::setw(10) << "points| "  << std::setw(10) << intToScore(score1, 1) << " | " << intToScore(score2, 2); //Scores
        std::cout << std::endl << std::setw(10) << "games | "  << std::setw(10) << games1 << " | " << games2 << std::endl; //Games
    }


    std::string serving(int player){ //Is used to print the asterix next to the server.
        if (player == server){
            return "*";
        }
        return " ";
    }


    int scoreTranslation(int score, int player){ //The scoring logic. Returns a number so can't return "AD"
        
        if (score1<=3 && score2<=3){
            if (score==0){
                return 0;
            }
            if (score==1){
                return 15;
            }
            if (score==2){
                return 30;
            }
            if (score==3){
                return 40;
            }
        }

        if ((score1==3 && score2==2) || (score1==2 && score2==3)){
            if ((score1 > score2) && player==1){
                return 40;
            }
            if ((score2 > score1) && player==2){
                return 40;
            }
            return 30;
        }

        if (score1==3 && score2 == 3){
            return 40;
        }

        if (score1>=3 && score2>=3){
            if ((score1 == score2 + 1)){
                if (player==1){
                    return -10; // -10 = Advantage
                }
            }
            if ((score2 == score1 + 1)){
                if (player==2){
                    return -10; // -10 = Advantage
                }
            }
            return 40; // Watched a game of tennis and it goes back to 40 from "AD-40"
        }

        return -5;
         
    }


    std::string intToScore(int score, int player){ //Takes the result of the logic, and returns a string. (Implemented to get "AD")
        int value = scoreTranslation(score, player);

        switch (value){
            case 0: return "0";
            case 15: return "15";
            case 30: return "30";
            case 40: return "40";
            case -10: return "AD";
        }
        return "Error";
    }


    std::string intToSpeach(int score, int player){ //Returns what umpire should say.
        int value = scoreTranslation(score, player);

        switch (value){
            case 0: return "love";
            case 15: return "fifteen";
            case 30: return "thirty";
            case 40: return "fourty";
            case -10: return "advantage";
        }
        return "Error";
    }


    int checkGameWon(){ //Checking if someone has won the game, uses the reset function.
        if (score1 >3 && score1 >= score2 + 2){
            games1++;
            reset();
            gameWinner = 1;
            return 1;
        }
        if (score2 >3 && score2 >= score1 + 2){
            games2++;
            reset();
            gameWinner = 2;
            return 2;
        }
        return 0;
    }


    void reset(){ //Resets the scores and swaps the player serving.
        score1 = 0;
        score2 = 0;

        if (server==1){
            server=2;
            return;
        }
        if (server==2){
            server=1;
            return;
        }

    }


    void checkMatchWon(){ //Checks if someone has 3 games. If they do, the game loop ends.
        if (games1>=3 || games2>=3){
            if (games1 > games2){
                std::cout << player1 << " Wins the Series!" << std::endl;

            }
            else{
                std::cout << player2 << " Wins the Series!" << std::endl;
                
            }
            running = false;
        }
    
    }

    public:

    //Constructor
    TennisMatch(std::string _player1, std::string _player2){
        player1 = _player1;
        player2 = _player2;
    }

    //Functions
    void play(){ // function that runs everything when called.

        announcement();
        scoreReading();

        while (running){

            addScoreToWinner();
            checkGameWon();
            announcement();
            scoreReading();
            checkMatchWon();

            //announcement();
            
        }
    }
};


int main(){

//Gets the inputs for the names of the people playing.
std::string string1; std::string string2; 
std::cout << "Enter the names of the players: " << std::endl << "Player 1 : ";
std::cin >> string1;
std::cout << "Player 2 : ";
std::cin >> string2;
std::cout << std::endl;

//Initializes class
TennisMatch match(string1, string2);

//Starts game loop
match.play();

return 0;

}