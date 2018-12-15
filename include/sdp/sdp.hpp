// Copyright 2018 Jan Deinhard

#ifndef LIBSDP_SESSIONDESCRIPTION_H
#define LIBSDP_SESSIONDESCRIPTION_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>

namespace sdp {

struct Origin {
    std::string userName;
    std::string sessionId;
    std::string sessionVersion;
    std::string netType;
    std::string addrType;
    std::string unicastAddress;
};

struct Connection {
    std::string netType;
    std::string addrType;
    std::string connectionAddress;
};

struct Bandwidth {
    std::string bwType;
    unsigned int bandwidth;
};

struct RepeatTime {
    unsigned int repeatInterval;
    unsigned int activeDuration;
    std::vector<unsigned int> offsetsFromStartTime;
};

struct TimeZoneAdjustment {
    unsigned int adjustmentTime;
    unsigned int offset;
};

struct Time {
    unsigned int startTime;
    unsigned int stopTime;
    std::vector<sdp::RepeatTime> repeatTimes;
};

struct TimeFields {
    std::vector<Time> times;
    std::vector<TimeZoneAdjustment> timeZoneAdjustments;
};

struct Media {
    std::string mediaType;
    unsigned int port;
    unsigned int numberPorts;
    std::string protocol;
    std::vector<std::string> format;
};

struct MediaDescription {
    Media media;
    std::string information;
    std::vector<Connection> connections;
    std::vector<Bandwidth> bandwidths;
    std::string key;
    std::vector<std::string> attributes;
};

struct SessionDescription {
    unsigned int version;
    Origin origin;
    std::string sessionName;
    std::string information;
    std::string uri;
    std::vector<std::string> emailAddresses;
    std::vector<std::string> phoneNumbers;
    Connection connection;
    std::vector<Bandwidth> bandwidths;
    TimeFields timeFields;
    std::string key;
    std::vector<std::string> attributes;
    std::vector<MediaDescription> mediaDescriptions;
};

bool parse(const std::string &input, SessionDescription *s);

bool parse(std::istream &input, SessionDescription *s);

void generate(SessionDescription *s, std::ostream &os);

}   // namespace sdp

#endif  // LIBSDP_SESSIONDESCRIPTION_H
