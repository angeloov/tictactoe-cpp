#include "MyWindow.hpp"

#include <pangomm/attributes.h>
#include <pangomm/attrlist.h>

#include "Socket.hpp"

MyWindow::MyWindow() : currentTurn("O") {
  // s.sendToServer("CREATEROOM");
  // std::string msg = s.receiveFromServer();
  // std::cout << "From server: " << msg << std::endl;
  // std::string msg = s.receiveFromServer();
  // std::cout << msg << std::endl;

  Glib::RefPtr<Gio::SimpleActionGroup> actionGroup = Gio::SimpleActionGroup::create();
  actionGroup->add_action("createRoom", sigc::mem_fun(*this, &MyWindow::onCreateRoom));

  Glib::RefPtr<Gtk::Builder> m_refBuilder = Gtk::Builder::create();
  app->set_accel_for_action("example.new", "<Primary>n");

  Glib::ustring ui_info =
  "<interface>"
  "  <menu id='menubar'>"
  "    <submenu>"
  "      <attribute name='label' translatable='yes'>_File</attribute>"
  "      <section>"
  "        <item>"
  "          <attribute name='label' translatable='yes'>_New</attribute>"
  "          <attribute name='action'>example.new</attribute>"
  "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
  "        </item>"
  "      </section>"
  "      <section>"
  "        <item>"
  "          <attribute name='label' translatable='yes'>_Quit</attribute>"
  "          <attribute name='action'>example.quit</attribute>"
  "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
  "        </item>"
  "      </section>"
  "    </submenu>"
  "</interface>";

  m_refBuilder->add_from_string(ui_info);

  setupGridContainer();
  setupGameButtons();
  setupCurrentTurnLabel();
  updateCurrentTurnLabel("Is't " + currentTurn + "'s turn");

  set_title("Tic Tac Toe");
  set_default_size(WIDTH, HEIGHT);

  displayUserInterface();
}

void MyWindow::onCreateRoom() {
  s.sendToServer("CREATEROOM");
  std::string res = s.receiveFromServer();
  std::cout << res << std::endl;
}

void MyWindow::displayUserInterface() {
  Gtk::Box mainContainer(Gtk::Orientation::VERTICAL, 0);

  mainContainer.append(currentTurnLabel);
  mainContainer.append(gridContainer);

  set_child(mainContainer);
}

void MyWindow::onButtonClicked(int buttonIndex) {
  std::string &currentSpotInMatrix =
      spotMatrix[buttonIndex / 3][buttonIndex % 3];

  if (currentSpotInMatrix == "" && !matchIsEnded) {
    currentSpotInMatrix = currentTurn;                    // update game matrix
    gameButtonsList[buttonIndex].set_label(currentTurn);  // update UI

    // check if tic tac toe was made
    if (someoneWonTheGame()) {
      matchIsEnded = true;
      updateCurrentTurnLabel(currentTurn + " won the game!");
      return;
    }

    if (numberOfMoves == 9) {
      matchIsEnded = true;
      updateCurrentTurnLabel("It's a tie!");
      return;
    }

    currentTurn = (currentTurn == "X") ? "O" : "X";  // set next turn
    updateCurrentTurnLabel("Is't " + currentTurn + "'s turn");
  }
}

bool MyWindow::someoneWonTheGame() {
  for (int row = 0; row < 3; row++) {
    bool valuesInRowAreTheSame = true;

    for (int col = 0; col < 3; col++)
      if (spotMatrix[row][col] != currentTurn) valuesInRowAreTheSame = false;

    if (valuesInRowAreTheSame) return true;
  }

  for (int col = 0; col < 3; col++) {
    bool valuesInColumnAreTheSame = true;

    for (int row = 0; row < 3; row++)
      if (spotMatrix[row][col] != currentTurn) valuesInColumnAreTheSame = false;

    if (valuesInColumnAreTheSame) return true;
  }

  // left hand diagonal and right hand diagonal
  if ((spotMatrix[0][0] == currentTurn && spotMatrix[1][1] == currentTurn &&
       spotMatrix[2][2] == currentTurn) ||
      (spotMatrix[0][2] == currentTurn && spotMatrix[1][1] == currentTurn &&
       spotMatrix[2][0] == currentTurn))
    return true;

  return false;
}

void MyWindow::updateCurrentTurnLabel(std::string text) {
  currentTurnLabel.set_text(text);
}

/*
 * -------------------- SETUP METHODS --------------------
 */

void MyWindow::setupCurrentTurnLabel() {
  Pango::AttrList attrList;

  Pango::Attribute weightAttribute =
      Pango::Attribute::create_attr_weight(Pango::Weight_Wrapper::Weight::BOLD);
  Pango::Attribute fontSizeAttribute =
      Pango::Attribute::create_attr_size(1024 * 10);

  attrList.insert(weightAttribute);
  attrList.insert(fontSizeAttribute);

  currentTurnLabel.set_attributes(attrList);
  currentTurnLabel.set_margin(16);
}

void MyWindow::setupGameButtons() {
  // create 9 buttons and insert them in gameButtonsList
  for (int i = 0; i < 9; i++) gameButtonsList.push_back(Gtk::Button(" "));

  // insert the 9 buttons in a grid widget
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      gridContainer.attach(gameButtonsList[(row * 3) + col], col, row);
    }
  }

  // attach onButtonClicked to each button
  for (int i = 0; i < gameButtonsList.size(); i++) {
    gameButtonsList[i].signal_clicked().connect(
        sigc::bind(sigc::mem_fun(*this, &MyWindow::onButtonClicked), i));
  }
}

void MyWindow::setupGridContainer() {
  gridContainer.set_expand(true);
  gridContainer.set_row_homogeneous(true);     // rows all have same height
  gridContainer.set_column_homogeneous(true);  // columns all have same height
}
