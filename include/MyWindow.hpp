#pragma once
#include <gtkmm.h>
#include <vector>

class MyWindow : public Gtk::Window {
 public:
  MyWindow();

  const int WIDTH = 300;
  const int HEIGHT = 380;

  // widgets members
  std::vector<Gtk::Button> gameButtonsList;
  Gtk::Grid gridContainer;

  Gtk::Label currentTurnLabel;
  void updateCurrentTurnLabel(std::string text);
  void displayUserInterface();

  // game members
  int numberOfMoves = 0;
  bool matchIsEnded = false;
  std::string currentTurn;
  std::string spotMatrix[3][3] = {};

  void onButtonClicked(int buttonIndex);
  bool someoneWonTheGame();

 private:
  void setupGameButtons();
  void setupGridContainer();
  void setupCurrentTurnLabel();
};
