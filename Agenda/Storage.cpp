#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Storage.hpp"
#include "Path.hpp"
using namespace std;

shared_ptr<Storage> Storage::m_instance = NULL;

Storage::Storage() {
    m_dirty = false;
    this->readFromFile();
}

Storage::~Storage() {
    if(m_dirty) this->writeToFile();
}

vector<string> stringToVector(string t_str) {
    stringstream ss(t_str);
    string item;
    vector<std::string> participatorlist;
    while (getline(ss, item, '&')) {
        participatorlist.push_back(item);
    }
    return participatorlist;
}

bool Storage::readFromFile() {
    ifstream users(Path::userPath,ios::in);
    ifstream meetings(Path::meetingPath, ios::in);
    if(!(users.good() && meetings.good())) {
        return false;
    }
    string line;
    while(getline(users, line)) {
        if(line.length() == 0) {
            continue;
        }
        stringstream ss(line);
        string str;
        vector<string> data;
        while (getline(ss, str, ',')) {
            data.push_back(str);
        }
        if(data.size() != 4) {
            continue;
        }
        for (auto &x : data) {
            x = x.substr(1, x.size() - 2);
        }
        User toAdd = User(data[0], data[1], data[2], data[3]);
        m_userList.push_back(toAdd);
    }
    users.close();

    while(getline(meetings, line)) {
        if (line.length() == 0) {
            continue;
        }
        stringstream ss(line);
        string str;
        vector<string> data;
        while (getline(ss, str, ',')) {
            data.push_back(str);
        }
        for (auto &x : data) {
            x = x.substr(1, x.size() - 2);
        }
        Meeting toAdd = Meeting(data[0], stringToVector(data[1]), data[2], data[3], data[4]);
        m_meetingList.push_back(toAdd);
    }
    return true;
}

bool Storage::writeToFile() {
    return 1;
}

shared_ptr<Storage> Storage::getInstance(void) {
    if(m_instance == NULL) {
        m_instance = shared_ptr<Storage>(new Storage);
    }
    return m_instance;
}

void Storage::createUser(const User & t_user) {
    m_userList.push_back(t_user);
    m_dirty = true;
}

list<User> Storage::queryUser(function<bool(const User &)> filter) const {
    list<User> fitedUsers;
    for (auto &x : m_userList) {
        if (filter(x)) fitedUsers.push_back(x);
    }
    return fitedUsers;
}

int Storage::updateUser(function<bool(const User &)> filter,
                        function<void(User &)> switcher) {
    int count = 0;
    for (auto &x : m_userList) {
        if (filter(x)) {
            switcher(x);
            count++;
            m_dirty = true;
        }
    }
    return count;
}

int Storage::deleteUser(function<bool(const User &)> filter) {
    int count = 0;
    for (auto it = m_userList.begin(); it != m_userList.end();) {
        if (filter(*it)) {
            it = m_userList.erase(it);
            count++;
            m_dirty = true;
        }
        else {
            it++;
        }
    }
    return count;
}

void Storage::createMeeting(const Meeting &t_meeting) {
    m_meetingList.push_back(t_meeting);
    m_dirty = true;
}

list<Meeting> Storage::queryMeeting(function<bool(const Meeting &)> filter) const {
    list<Meeting> fitedMeetings;
    for(auto &x : m_meetingList) {
        if (filter(x)) fitedMeetings.push_back(x);
    }
    return fitedMeetings;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                           std::function<void(Meeting &)> switcher) {
    int count = 0;
    for (auto &x : m_meetingList) {
        if (filter(x)) {
            switcher(x);
            count++;
            m_dirty = true;
        }
    }
    return count;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
    int count = 0;
    for (auto it = m_meetingList.begin(); it != m_meetingList.end();) {
        if (filter(*it)) {
            it = m_meetingList.erase(it);
            count++;
            m_dirty = true;
        }
        else {
            it++;
        }
    }
    return count;
}

bool Storage::sync() {
    return writeToFile();
}
