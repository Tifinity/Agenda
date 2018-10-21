#include "Meeting.hpp"
#include "Date.hpp"
#include "User.hpp"
#include <vector>
using namespace std;

Meeting::Meeting(const string &t_sponsor, 
                 const vector<string> &t_participator,
                 const Date &t_startDate, 
                 const Date &t_endDate,
                 const string &t_title)
    : m_sponsor(t_sponsor),
      m_participators(t_participator),
      m_startDate(t_startDate),
      m_endDate(t_endDate),
      m_title(t_title) {}

Meeting::Meeting(const Meeting &t_meeting)
    : m_sponsor(t_meeting.m_sponsor),
      m_participators(t_meeting.m_participators),
      m_startDate(t_meeting.m_startDate),
      m_endDate(t_meeting.m_endDate),
      m_title(t_meeting.m_title) {}

string Meeting::getSponsor(void) const {
    return m_sponsor; 
}

void Meeting::setSponsor(const string &t_sponsor) { 
    m_sponsor = t_sponsor; 
}

vector<string> Meeting::getParticipator() const {
    return m_participators;
}

void Meeting::setParticipator(const vector<string> &t_participator) {
    m_participators = t_participator;
}

void Meeting::addParticipator(const std::string &t_participator) {
    if (isParticipator(t_participator)) return;
    m_participators.push_back(t_participator);
}

void Meeting::removeParticipator(const std::string &t_participator) {
    if (!isParticipator(t_participator)) return;
    for (auto it = m_participators.begin(); it != m_participators.end();) {
        if (*it == t_participator) it = m_participators.erase(it);
        else it++;
    }
}

Date Meeting::getStartDate() const { 
    return m_startDate;
}

void Meeting::setStartDate(const Date &t_startTime) {
    m_startDate = t_startTime;
}

Date Meeting::getEndDate() const { 
    return m_endDate;
}

void Meeting::setEndDate(const Date &t_endTime) { 
    m_endDate = t_endTime; 
}

string Meeting::getTitle() const {
    return m_title; 
}

void Meeting::setTitle(const string &t_title) {
    m_title = t_title; 
}

bool Meeting::isParticipator(const string &t_username) const {
    for (auto &x : m_participators) {
        if (x == t_username) return true;
    }
    return false;
}