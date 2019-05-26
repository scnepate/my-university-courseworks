#ifndef HW4_TANK_H
#define HW4_TANK_H

#include"Player.h"

class Tank : public Player{
  /**
   * Attack damage 25
   * Heal power 0
   * Max HP 1000
   * Goal Priorities -> {TO_ENEMY,ATTACK,CHEST} in decreasing order
   * Class abbreviation -> "ta" or "TA"
   * Can move to adjacent up, down, left or right square
   * Can attack to adjacent up, down, left or right square
   *
   */

  private:
    private:
    int attack_damage;
    int heal_power;
    int max_hp;
    std::vector <Goal> goals;
    std::string abbrevation;
  public:
   Tank (uint id, int x, int y, Team team);
   virtual ~Tank ();
   virtual int getAttackDamage () const;
   virtual int getHealPower() const ;
	 virtual int getMaxHP() const;

  /**
   * For each subclass of Player there are different priority lists defined
   * that controls the next action to take for that Player. It is given in the
   * header of the subclasses.
   *
   * @return the goal priority list for the Player
   */
   virtual std::vector<Goal> getGoalPriorityList();
  /**
   * @return the class abbreviation of player, if the player is on the barbarian
   * team, the abbreviation will consist of uppercase characters, otherwise it
   * will consist of lowercase characters.
   *
   */

   virtual const std::string getClassAbbreviation() const;

  /**
   * @Important The coordinates may not be on the board.
   *
   * @return the coordinates that the unit is able to attack given the position
   * of the unit. Empty vector if the unit cannot attack.
   */

   virtual std::vector<Coordinate> getAttackableCoordinates();

  /**
   * @Important The coordinates may not be on the board.
   *
   * @return the coordinates the unit is able to move given the position of the
   * unit. Empty vector if the unit cannot move.
   */
   virtual std::vector<Coordinate> getMoveableCoordinates();

  /**
   *
   * @return the coordinates the unit is able to heal allies given the position of the
   * unit. Empty vector if none available.
   */
   virtual std::vector<Coordinate> getHealableCoordinates();
};

#endif
