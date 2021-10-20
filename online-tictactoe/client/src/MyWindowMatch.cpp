#include <iostream>

#include "MyWindow.hpp"
#include "Socket.hpp"
#include "timercpp.h"

using namespace std;

std::vector<std::string> splitStr(const std::string &s) {
  int i = 0;
  std::string temp = "";
  std::vector<std::string> vec;

  for (size_t i = 0; i != s.size(); i++) {
    if (s[i] != ' ') {
      temp += s[i];
    } else {
      vec.push_back(temp);
      temp = "";
    }
  }

  vec.push_back(temp);

  return vec;
}

void MyWindow::joinMatch() {
  std::cout << " a" << std::endl;
  // Timer t;
  // t.setTimeout([this]() { std::cout << "CIAO!" << std::endl; }, 1000);
}

void MyWindow::createMatch() {
  s.sendToServer("CREATEROOM");
  std::string msg = s.receiveFromServer();

  std::vector<std::string> v = splitStr(msg);
  std::string matchCode = v[2];
  std::string text("Match code: " + matchCode + '\0');

  m_pDialog.reset(new Gtk::MessageDialog(*this, "Created a room successfully"));
  m_pDialog->set_secondary_text(text);
  m_pDialog->set_modal(true);
  m_pDialog->set_hide_on_close(true);
  m_pDialog->signal_response().connect(
      sigc::hide(sigc::mem_fun(*m_pDialog, &Gtk::Widget::hide)));

  m_pDialog->show();
}

void MyWindow::quitApp() { hide(); }
