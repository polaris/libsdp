// Copyright 2018 Jan Deinhard

#include "sdp/sdp.hpp"

#include <iostream>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>

BOOST_FUSION_ADAPT_STRUCT(
    sdp::Origin,
    (std::string, userName)
    (std::string, sessionId)
    (std::string, sessionVersion)
    (std::string, netType)
    (std::string, addrType)
    (std::string, unicastAddress))

BOOST_FUSION_ADAPT_STRUCT(
    sdp::Connection,
    (std::string, netType)
    (std::string, addrType)
    (std::string, connectionAddress))

BOOST_FUSION_ADAPT_STRUCT(
    sdp::Bandwidth,
    (std::string, bwType)
    (unsigned int, bandwidth))

BOOST_FUSION_ADAPT_STRUCT(
    sdp::RepeatTime,
    (unsigned int, repeatInterval)
    (unsigned int, activeDuration)
    (std::vector<unsigned int>, offsetsFromStartTime))

BOOST_FUSION_ADAPT_STRUCT(
    sdp::TimeZoneAdjustment,
    (unsigned int, adjustmentTime)
    (unsigned int, offset))

BOOST_FUSION_ADAPT_STRUCT(
    sdp::Time,
    (unsigned int, startTime)
    (unsigned int, stopTime)
    (std::vector<sdp::RepeatTime>, repeatTimes))

BOOST_FUSION_ADAPT_STRUCT(
    sdp::TimeFields,
    (std::vector<sdp::Time>, times)
    (std::vector<sdp::TimeZoneAdjustment>, timeZoneAdjustments))

BOOST_FUSION_ADAPT_STRUCT(
    sdp::Media,
    (std::string, mediaType)
    (unsigned int, port)
    (unsigned int, numberPorts)
    (std::string, protocol)
    (std::vector<std::string>, format))

BOOST_FUSION_ADAPT_STRUCT(
    sdp::MediaDescription,
    (sdp::Media, media)
    (std::string, information)
    (std::vector<sdp::Connection>, connections)
    (std::vector<sdp::Bandwidth>, bandwidths)
    (std::string, key)
    (std::vector<std::string>, attributes))

BOOST_FUSION_ADAPT_STRUCT(
    sdp::SessionDescription,
    (unsigned int, version)
    (sdp::Origin, origin)
    (std::string, sessionName)
    (std::string, information)
    (std::string, uri)
    (std::vector<std::string>, emailAddresses)
    (std::vector<std::string>, phoneNumbers)
    (sdp::Connection, connection)
    (std::vector<sdp::Bandwidth>, bandwidths)
    (sdp::TimeFields, timeFields)
    (std::string, key)
    (std::vector<std::string>, attributes)
    (std::vector<sdp::MediaDescription>, mediaDescriptions))

namespace sdp {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct SessionDescriptionGrammar
: qi::grammar<Iterator, SessionDescription(), ascii::space_type> {
    SessionDescriptionGrammar()
    : SessionDescriptionGrammar::base_type(start) {
        auto token = qi::copy(+(qi::char_('!') | qi::char_('/') |
                     qi::char_('#', '\'') | qi::char_('*', '+') |
                     qi::char_('-', '.') | qi::char_('0', '9') |
                     qi::char_('A', 'Z') | qi::char_('^', '~')));
        auto text = qi::copy(+(qi::char_ - qi::eol));
        auto eol = qi::copy(qi::eol | qi::eoi);

        start = versionField >>
                originField >>
                sessionNameField >>
                -informationField >>
                -uriField >>
                *emailField >>
                *phoneField >>
                -connectionField >>
                *bandwidthField >>
                timeFields >>
                -keyField >>
                *attributeField >>
                +mediaDescField;

        mediaDescField = mediaField >>
                         -informationField >>
                         *connectionField >>
                         *bandwidthField >>
                         -keyField >>
                         *attributeField;

        versionField =
            qi::lit("v") >> qi::lit("=") >> qi::lexeme[qi::int_ >> eol];
        originField =
            qi::lit("o") >> qi::lit("=") >>
                qi::lexeme[+qi::alnum >> " " >> +qi::digit >> " " >>
                +qi::digit >> " " >> token >> " " >> token >> " " >>
                token >> eol];
        sessionNameField =
            qi::lit("s") >> qi::lit("=") >> qi::lexeme[text >> eol];
        informationField =
            qi::lit("i") >> qi::lit("=") >> qi::lexeme[text >> eol];
        uriField = qi::lit("u") >> qi::lit("=") >> qi::lexeme[text >> eol];
        emailField = qi::lit("e") >> qi::lit("=") >> qi::lexeme[text >> eol];
        phoneField = qi::lit("p") >> qi::lit("=") >> qi::lexeme[text >> eol];
        connectionField =
            qi::lit("c") >> qi::lit("=") >>
                qi::lexeme[token >> " " >> token >> " " >> token >> eol];
        bandwidthField =
            qi::lit("b") >> qi::lit("=") >>
                qi::lexeme[token >> ":" >> qi::int_ >> eol];
        timeFields =
            qi::lexeme[+(qi::lit("t") >> qi::lit("=") >>
                qi::int_ >> " " >> qi::int_ >>
                    *(eol >> qi::lit("r") >> qi::lit("=") >>
                        qi::int_ >> " " >> qi::int_ >> +(" " >> qi::int_)) >>
                    eol) >>
                        -(qi::lit("z") >> qi::lit("=") >>
                            +(qi::int_ >> " " >> qi::int_ >>
                            -qi::char_(' ')) >> eol)];
        keyField = qi::lit("k") >> qi::lit("=") >> qi::lexeme[text >> eol];
        attributeField =
            qi::lit("a") >> qi::lit("=") >> qi::lexeme[text >> eol];
        mediaField = qi::lit("m") >> qi::lit("=") >>
            qi::lexeme[token >> " " >> qi::int_ >> -("/" >> qi::int_) >> " " >>
            token >> +(" " >> token) >> eol];
    }

    qi::rule<Iterator, SessionDescription(), ascii::space_type> start;
    qi::rule<Iterator, unsigned int, ascii::space_type> versionField;
    qi::rule<Iterator, Origin(), ascii::space_type> originField;
    qi::rule<Iterator, std::string(), ascii::space_type> sessionNameField;
    qi::rule<Iterator, std::string(), ascii::space_type> informationField;
    qi::rule<Iterator, std::string(), ascii::space_type> uriField;
    qi::rule<Iterator, std::string(), ascii::space_type> emailField;
    qi::rule<Iterator, std::string(), ascii::space_type> phoneField;
    qi::rule<Iterator, Connection(), ascii::space_type> connectionField;
    qi::rule<Iterator, Bandwidth(), ascii::space_type> bandwidthField;
    qi::rule<Iterator, TimeFields(), ascii::space_type> timeFields;
    qi::rule<Iterator, std::string(), ascii::space_type> keyField;
    qi::rule<Iterator, std::string(), ascii::space_type> attributeField;
    qi::rule<Iterator, Media(), ascii::space_type> mediaField;
    qi::rule<Iterator, MediaDescription(), ascii::space_type> mediaDescField;
};

bool parse(const std::string &input, SessionDescription *s) {
    SessionDescriptionGrammar<std::string::const_iterator> grammar;
    return phrase_parse(input.begin(), input.end(),
        grammar, boost::spirit::ascii::space, *s);
}

bool parse(std::istream &input, SessionDescription *s) {
    input.unsetf(std::ios::skipws);

    boost::spirit::istream_iterator begin(input);
    boost::spirit::istream_iterator end;

    SessionDescriptionGrammar<boost::spirit::istream_iterator> grammar;
    return phrase_parse(begin, end, grammar, boost::spirit::ascii::space, *s);
}

void generate(SessionDescription *s, std::ostream &os) {
    os << "v=" << s->version << "\n"
       << "o=" << s->origin.userName << " " << s->origin.sessionId << " "
               << s->origin.sessionVersion << " " << s->origin.netType
               << " " << s->origin.addrType << " " << s->origin.unicastAddress
               << "\n"
       << "s=" << s->sessionName << "\n";
    if (s->information.length() > 0) {
        os << "i=" << s->information << "\n";
    }
    if (s->uri.length() > 0) {
        os << "u=" << s->uri << "\n";
    }
    for (const auto& e : s->emailAddresses) {
        os << "e=" << e << "\n";
    }
    for (const auto& n : s->phoneNumbers) {
        os << "p=" << n << "\n";
    }
    os << "c=" << s->connection.netType << " " << s->connection.addrType
               << " " << s->connection.connectionAddress << "\n";
    for (const auto& b : s->bandwidths) {
        os << "b=" << b.bwType << ":" << b.bandwidth << "\n";
    }
    for (const auto& t : s->timeFields.times) {
        os << "t=" << t.startTime << " " << t.stopTime << "\n";
        for (const auto& r : t.repeatTimes) {
            os << "r=" << r.repeatInterval << " " << r.activeDuration;
            for (const auto& o : r.offsetsFromStartTime) {
                os << " " << o;
            }
            os << "\n";
        }
    }
    if (!s->timeFields.timeZoneAdjustments.empty()) {
        os << "z=";
        std::size_t i = 0;
        for (; i < s->timeFields.timeZoneAdjustments.size() - 1; ++i) {
            os << s->timeFields.timeZoneAdjustments[i].adjustmentTime << " "
               << s->timeFields.timeZoneAdjustments[i].offset << " ";
        }
        os << s->timeFields.timeZoneAdjustments[i].adjustmentTime << " "
           << s->timeFields.timeZoneAdjustments[i].offset << "\n";
    }
    if (s->key.length() > 0) {
        os << "k=" << s->key << "\n";
    }
    for (const auto &a : s->attributes) {
        os << "a=" << a << "\n";
    }
    for (const auto &m : s->mediaDescriptions) {
        os << "m=" << m.media.mediaType << " " << m.media.port;
        if (m.media.numberPorts > 1) {
            os << "/" << m.media.numberPorts << " ";
        } else {
            os << " ";
        }
        os << m.media.protocol << " ";
        if (!m.media.format.empty()) {
            std::size_t i = 0;
            for (; i < m.media.format.size() - 1; ++i) {
                os << m.media.format[i] << " ";
            }
            os << m.media.format[i];
        }
        os << "\n";
        for (const auto &a : m.attributes) {
            os << "a=" << a << "\n";
        }
    }
}

}   // namespace sdp
