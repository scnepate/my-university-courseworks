#ifndef HW4_ARCHER_H
#define HW4_ARCHER_H

#include"Player.h"

class Archer : public Player{
  /**
   * Attack damage 50
   * Heal power 0
   * Max HP 200
   * Goal Priorities -> {ATTACK}
   * Class abbreviation -> "ar" or "AR"
   * Not able to move at all.
   * Can attack to a range of 2 squares directly up, down, left or right, from
   * its coordinate.
   */

  private:
    int attack_damage;
    int heal_power;
    int max_hp;
    std::vector <Goal> goals;
    std::string abbrevation;
  public:
   Archer (uint id, int x, int y, Team team);
   virtual ~Archer ();
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
