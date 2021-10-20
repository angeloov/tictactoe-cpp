#pragma once
#include <gtkmm.h>
#include <vector>
#include "Socket.hpp"

class MyWindow : public Gtk::Window {
 public:
  MyWindow();

  Socket s;  // TCP network socket
  const int WIDTH = 300;
  const int HEIGHT = 380;

  Glib::RefPtr<Gio::SimpleActionGroup> actionGroup;
  Glib::RefPtr<Gtk::Builder> m_refBuilder;

  std::unique_ptr<Gtk::MessageDialog> m_pDialog; // Game code dialog

  // widgets members
  std::vector<Gtk::Button> gameButtonsList;
  Gtk::Box mainContainer;
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

  void joinMatch();
  void createMatch();
  void quitApp();

 private:
  void setupGameButtons();
  void setupGridContainer();
  void setupCurrentTurnLabel();
};
