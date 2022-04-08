/**
* 		James Peou | May 7th 2019
*		CPSC 121 M/W 11:30 - 12:15 P.M
*		Section 19 (Wed)
*
*		In this assignment I made a simplified version of dungeons and dragons 
*		Lots of derived classes were used to make this assingment and they were derived off
*		of the same class. Virtual functions were also used to help this lab since the pointers
*		could access them since they are abstract classes.
*/

#include <iostream>
#include <cmath>
#include <string>
#include <ctime> 
#include <memory>


using namespace std;

void mainBattle(); // the main fight sequence for the entire game 


class CommonStatistic {
	protected: 
		string name;
		int hitPoints; // hp for the charcters
		int attackDamage; // damage for the characters
		int attackDie; // die for the character, they only have 1 die 
		int armor; // armor value that blocks the damage from attackDamage
		int healingDie; // healing die for the player
		int sideOfHD; // the amount of sides that the healing die has
		int maxHitPoints; // used to stop the player from overhealing with the healing mechaninc
		int dmgTaken; //  allows for the characters to take damage
		int attackModifier; // bonus damage for all of the characters and depneds on their class for special stuff
		int initiativeModifier; // value added to the firstTurn to see who goes first in a fight
		int firstTurn; // used to see who goes first 
		
	public:
		CommonStatistic() {
			
			attackDie = 1; // players defaultly only have 1 die to use to fight

		}
		int  getAttackDamage() { // returns damage value from the character
			return attackDamage;
		}
		int getHP() { // returns hp from the characters
			return hitPoints;
		}
		int getHealingDie() { // return the die for the player
			return healingDie;
		}
		int getAttackDie() { // returns the die for the characters
			return attackDie;
		}
		string getName() { // returns the name of the characters
			return name;
		}
		int getArmor() { // returns the armor value for the characters
			return armor;
		}
		int getAttackModifier() { // return the attack damage bonus 
			return attackModifier;
		}
		int getFirstTurn() { // used to see who would go first
			return firstTurn;
		}
		
		void magicalFairy() { // heals the player after winning battle
			
			cout << "A magical fairy visits you, health has been reset to 20!" << endl;
			hitPoints = 20; 
		}
		void rollHealDie() {
			int totalHeal; // total healing after roll
			healingDie = ((rand() % sideOfHD + 1) + (rand() % sideOfHD + 1)); // player only has 2 heal die 
			totalHeal = hitPoints + healingDie;
			if (totalHeal >  maxHitPoints) { // stops from healing the chracter over max health
				hitPoints = 20;
			}
			else {
			hitPoints = hitPoints + healingDie; // re-updates health after healing
			}	
			cout << "Total HP now at: " << hitPoints << endl; // shows total health
			cout << "Total heal cap: " << maxHitPoints << endl;
		}
		// abstract base classes 
		virtual void printIntro() = 0; // prints the name of the chracter and then shows a voiceline
		virtual void takeDmg(int dmg) = 0; // allows for the characters to take damage
		virtual void isDead() = 0; // checks if the characters are dead 
		virtual void showStats() = 0; //  shows the stats of all of the players
		virtual void turnOneRoll() = 0; // value to see who goes first in a fight
		
};

class Warrior : public CommonStatistic {
	private:
		int initiativeModifier; // modifier to see who goes first in firstTurn
	public:
		Warrior() : CommonStatistic() { // assigning stats for the Warrior class
			name = "Carti"; 
			hitPoints = 20;
			maxHitPoints = 20; 
			attackModifier = 3;
			initiativeModifier = 4;
			healingDie = 2;
			sideOfHD = 5;
			armor = 5;
		}
		int getInitiativeModifier() { // returns the initiativeModifer of the character
			return initiativeModifier;
		}
		virtual void printIntro() { 
			cout << "You are now knight " << name << ", a ferocious mumble rapper" << endl;
			cout << "Hide it in my sock states " << name << endl; 
		}
		virtual void takeDmg(int dmg) { // the damage system of how the characters takes damage
			hitPoints = hitPoints - dmg;
				if (hitPoints < 0) {
				hitPoints = 0;
			}	
			cout << "Knight " << name << " has taken " << dmg << " and is now at "<< hitPoints << " HP"  << endl;
		}
		virtual void isDead() { // checks if the player has died 
			if (hitPoints == 0) {
				cout << "You Have died." << endl;
			}
		}
		virtual void showStats() { // shows the stats of the Warrior 
			cout << "Warrior Knight " <<  name << "'s current stats:" << endl;
			cout << "Health: " << hitPoints << endl;
			cout << "Healing Die: " << healingDie << " D5" << endl;
			cout << "Base attack Die: " <<  attackDie << " D6" << endl;
			cout << "Armor: " << armor << endl;
			cout << "Attack Modifier(Strength): " <<  attackModifier << endl;
			cout << "Initiative Modifer(Speed): " <<  initiativeModifier << endl << endl;
		}
		virtual void turnOneRoll() { // randomness factor of the rolls, rolls are 1-20 and then adds it to the modifier and then gets the final value
			firstTurn = rand()% 20 + 1;
			cout << "You rolled one dice (1-20): Initiative score of " << firstTurn << " + a speed modifier of " << initiativeModifier << " for a total of " << firstTurn + initiativeModifier << endl; // the warrior has a modifier that increases his chances of going first
			firstTurn = firstTurn + initiativeModifier; 
		}
};

class Mage : public CommonStatistic {
	/*
	*
	*
	* no privates needed since the mage has no modiifer to add to the firstTurn roll
	*
	*/
	public:
		Mage() : CommonStatistic() { // assigning stats to the Mage character
			name = "Eminem";
			hitPoints = 10;
			attackModifier = 7;
			armor = 2;
		}
		virtual void printIntro() {      
			cout << "A mage named " << name << " appears and is ready to save the rap game!" << endl;		
			cout << "Summa-lumma Dooma-lumma cries " << name << endl; 
		}
		virtual void takeDmg(int dmg) { // the damage system of how the characters takes damage
			hitPoints = hitPoints - dmg;
			if (hitPoints <= 0) {
				hitPoints = 0;
			}
			cout << "The mage has taken " << dmg << " and is now at " << hitPoints << " HP" << endl;
			
		}
		virtual void isDead() { // checks if the mage is dead 
			if (hitPoints == 0) {
				cout << "The Wizard has been Slain!" << endl;
			}
		}
			virtual void showStats() { // shows the stats of the Mage
				cout << "Wizard Mage " <<  name << "'s current stats:" << endl;
				cout << "Health: " << hitPoints << endl;
				cout << "Base attack Die: " <<  attackDie << " D4" << endl;
				cout << "Armor: " << armor << endl;
				cout << "Attack Modifier(Strength): " <<  attackModifier << endl << endl;
			}
		virtual void turnOneRoll() { // randomness factor of the rolls, rolls are 1-20 and then adds it to the modifier and then gets the final value
			firstTurn = rand()% 20 + 1;
			cout << "The mage rolled one dice (1-20): Initiative score of " << firstTurn << " and has no bonus speed modifier" << endl; // since the mage has no modifier nothing gets added 
		}
};

class Assassin : public CommonStatistic {
	private:
		int initiativeModifier;
	public:
		Assassin() : CommonStatistic() { // assigning stats to the Assassin character
			name = "Logic";
			hitPoints = 10;
			attackModifier = 3;
			armor = 3;
			initiativeModifier = 5;
		}
		string getName() { // returns the name of the character
			return name;
		}
		int getInitiativeModifier() { // returns the initiativeModifer of the character
			return initiativeModifier;
		}
		bool dodgeChance() { // dodge mechaninc for the rogue, only applies to the rogue
			int dodgePercent = rand() % 2; // has 0 - 1 chance of dodging, basically 50% chance to dodge an attack
			if (dodgePercent == 0) { // if dodge is 0 they dont dodge the attack
				return false;
			}
			else { // if its 1 they dodge the attack
				return true;
			}
		}
		
		virtual void printIntro() { // shows the intro of the character, and prints a phrase that they say
			cout << "A rogue named Assassin "  << name << " appears and is bi-racial!" << endl;
			cout << "Get schwifty my dudes whispered " <<  name << endl; 
		}
		virtual void takeDmg(int dmg) { // damage system for the character
			dodgeChance();
			if (dodgeChance() == 0) {
				hitPoints = hitPoints - dmg;
				if (hitPoints <= 0) {
				hitPoints = 0;
			}
			cout << "The Assassin has taken " << dmg << " and is now at " << hitPoints << " HP"  << endl;
			}
			else { 
				cout << "Assassin " << name << " dodged the attack!" << endl;
				cout << endl;
			}
		} 
		virtual void isDead() { // checks if this character has died
			if (hitPoints == 0) {
				cout << "The Assassin has been slain!" << endl;
			}
		}
		virtual void showStats() { // shows the stats of the Assassin
			cout << "Rogue Assassin " <<  name << "'s current stats:" << endl;
			cout << "Health: " << hitPoints << endl;
			cout << "Base attack Die: " <<  attackDie << " D4" << endl;
			cout << "Armor: " << armor << endl;
			cout << "Attack Modifier(Agility): " <<  attackModifier << endl;
			cout << "Initiative Modifer(Speed): " <<  initiativeModifier << endl;
			cout << "Dodge: 50% chance to dodge an incoming attack " << endl;
		}
		virtual void turnOneRoll() { // randomness factor of the rolls, rolls are 1-20 and then adds it to the modifier and then gets the final value
			firstTurn = rand()% 20 + 1;
			cout << "The Rogue rolled one dice (1-20): Initiative score of " << firstTurn << " + a speed modifier of " << initiativeModifier << " for a total of " << firstTurn + initiativeModifier << endl; // same as the warrior the Assassin has an increased chance of going first as well
			firstTurn = firstTurn + initiativeModifier; 
		}
};

int main () {
	
	mainBattle(); // the main battle sequence 
	system("pause");
	return 0;
}

void mainBattle() { // the main battle sequence creates the scenario for the player
	
	shared_ptr<Warrior> human = make_shared<Warrior>(); // pointers to classes and abstract classes 
	shared_ptr<Mage> enemy = make_shared<Mage>();
	shared_ptr<Assassin> enemyTwo = make_shared<Assassin>();
	
	int tempAttack = 0; // temporary value that always changes
	int choice; // choice for the main menu

		srand(time(0)); // used in order for the random number generator to work
		cout << endl; 
		
		human -> printIntro(); // 
		enemy -> printIntro();
		cout << endl;
		human -> showStats(); // shows the stats of the player
		enemy -> showStats(); // shows the stats of the enemy
		

		while (human -> getHP() > 0 && enemy -> getHP() > 0) { // constantly checking if the player or the enemy is 0 hp
			
			int damageRoll = rand()% 6 + 1;
			int damageRollTwo = rand()% 8 + 1;
			
			human -> turnOneRoll();
			enemy -> turnOneRoll();
	
			if (enemy -> getFirstTurn() < human -> getFirstTurn()) { // Takes into account of the initiativeModifer add with a dice roll of 1 - 20 and compares it to the players roll
				cout << endl;
				cout << "Your Move: " << endl;
				cout << "What will you do? " << endl; // main menu for the fight
				cout << "1: Attack" << endl;
				cout << "2: Heal" << endl;
				cin >> choice;
				if (choice == 2) { // heals the player
						human -> rollHealDie();
					}
					else if (choice == 1) { // choice system | attack system pointers point to the damage modifers and armor and then subtracts the value of the enemy. Damage is calculated by adding the attackModifer from the damageRoll and then subtracts the armor and final value is dealt to the HP of the characters
						cout << "You rolled one dice (1-6) damage score of " << damageRoll << " with a strength modifier of " <<  human -> getAttackModifier() << " for a total of " << damageRoll +  human -> getAttackModifier() << endl; 
						tempAttack = (damageRoll +  human -> getAttackModifier()) - (enemy -> getArmor());
						enemy -> takeDmg(tempAttack);
					}
				}		 
					else if (enemy -> getFirstTurn() > human -> getFirstTurn())  { // Takes into account of the initiativeModifer add with a dice roll of 1 - 20 and compares it to the players roll
					cout << "Wizard Eminem's turn: " << endl;
					cout << "The Wizard rolled one dice (1-4) damage score of " << damageRollTwo << " with a intellect modifier of " <<  enemy ->  getAttackModifier() << " for a total of " << damageRollTwo +  enemy -> getAttackModifier() << endl;
					tempAttack = (damageRoll +  enemy -> getAttackModifier()) - (human -> getArmor());
					human -> takeDmg(tempAttack);
					cout << endl << endl;
				}
				else if (enemy -> getFirstTurn() == human -> getFirstTurn()) {  // a conditional statement to check if both of the players roll the same value of the rolls and just re rolls 
					
					cout << "Both characters had the same roll......." << endl;
					cout << "Rerolling...." << endl;
					human -> turnOneRoll();
					enemy -> turnOneRoll();
				}
			}
			
			if (enemy -> getHP() == 0 ) { 
				
				enemy -> isDead(); // pointer to the isDead function 
				human -> magicalFairy(); // heals the player back to 20 HP if they kill the enemy
				
			} 
			
			enemyTwo -> printIntro(); // prints the introduction and a voiceline of enemyTwo
			cout << endl << endl;
			human -> showStats();
			enemyTwo -> showStats(); // shows the stats of enemyTwo
		
			while (human -> getHP() > 0 && enemyTwo -> getHP() > 0) { // constantly checking if the player or the enemy is 0 hp
			
				int damageRoll = rand()% 6 + 1;
				int damageRollTwo = rand()% 8 + 1;
			
				human -> turnOneRoll();
				enemyTwo -> turnOneRoll();
			
				if (enemyTwo -> getFirstTurn() < human -> getFirstTurn()) {
					cout << "Your Move: " << endl;
					cout << "What will you do? " << endl; // main menu
					cout << "1: Attack" << endl;
					cout << "2: Heal" << endl;
					cin >> choice;
					if (choice == 2) { // choice 
						human -> rollHealDie();
					}
					else if (choice == 1) { // choice system | attack system pointers point to the damage modifers and armor and then subtracts the value of the enemy. Damage is calculated by adding the attackModifer from the damageRoll and then subtracts the armor and final value is dealt to the HP of the characters
						cout << "You rolled one dice (1-6) damage score of " << damageRoll << " with a strength modifier of " <<  human -> getAttackModifier() << " for a total of " << damageRoll +  human -> getAttackModifier() << endl; 
						tempAttack = (damageRoll +  human -> getAttackModifier()) - (enemyTwo -> getArmor());
						enemyTwo -> takeDmg(tempAttack);
					}
				} 
					else if (enemyTwo -> getFirstTurn() > human -> getFirstTurn())  { // Takes into account of the initiativeModifer add with a dice roll of 1 - 20 and compares it to the players
						cout << "Assassin Logic's turn: " << endl;
						cout << "The Rogue rolled one dice (1-4) damage score of " << damageRollTwo << " with an agliity modifier of " <<  enemyTwo -> getAttackModifier() << " for a total of " << damageRollTwo +  enemy -> getAttackModifier() << endl;
						tempAttack = (damageRoll +  enemy -> getAttackModifier()) - (human -> getArmor());
						human -> takeDmg(tempAttack);
						cout << endl;
					}
					else if (enemyTwo -> getFirstTurn() == human -> getFirstTurn()) { // checks if the both parties have the same re roll then it rerolls again
						
						cout << "Both characters had the same roll......." << endl;
						cout << "Rerolling...." << endl;
						human -> turnOneRoll();
						enemyTwo -> turnOneRoll(); 
						
					}
					cout << endl;
					if (human -> getHP() == 0) { // check if player is dead
				
						human -> isDead(); // points to virtual function

				
					}	
						else if (enemyTwo -> getHP() == 0 ) { // if enemy has 0 HP the game is won!
						enemyTwo -> isDead();
						cout << "You saved the rap game!" << endl;
					}
	
	}
	
}