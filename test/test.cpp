// Copyright 2018 Jan Deinhard

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <sdp/sdp.hpp>

#include <sstream>

void verify(const std::string &expected);

TEST_CASE("Test 1") {
    const std::string expected{
        "v=0\n"
        "o=Alice 1234 1234 IN IP4 host.provider1.com\n"
        "s=Video von 987654\n"
        "c=IN IP4 host.provider2.com\n"
        "t=0 0\n"
        "m=audio 20000 RTP/AVP 97\n"
        "a=rtpmap:97 iLBC/8000\n"
        "a=fmtp:97 mode=30\n"
        "m=video 20001 RTP/AVP 31\n"
        "a=rtpmap:31 H261/90000\n"
    };
    verify(expected);
}

TEST_CASE("Test 2") {
    const std::string expected{
        "v=0\n"
        "o=Alice 1234 1234 IN IP4 host.provider1.com\n"
        "s=Video von 987654\n"
        "i=Foo Bar Baz\n"
        "u=http://www.example.com/foo\n"
        "e=jan.deinhard@gmail.com\n"
        "e=jan.deinhard@sennheiser.com\n"
        "p=+4940889234234\n"
        "p=+4916095628356\n"
        "c=IN IP4 host.provider2.com\n"
        "b=CS:1234\n"
        "t=34 6457757\n"
        "r=123 456 789 987\n"
        "z=666 999 123 456\n"
        "k=clear:asdjfhaslkdfhasjdf\n"
        "a=test\n"
        "m=audio 20000 RTP/AVP 97\n"
        "a=rtpmap:97 iLBC/8000\n"
        "m=video 20001 RTP/AVP 31\n"
        "a=rtpmap:31 H261/90000\n"
    };
    verify(expected);
}

TEST_CASE("Test 3") {
    const std::string expected{
        "v=0\n"
        "o=alice 2890844526 2890844526 IN IP4 host.atlanta.example.com\n"
        "s=Foo Bar Baz Que\n"
        "c=IN IP4 host.atlanta.example.com\n"
        "t=0 0\n"
        "m=audio 49170 RTP/AVP 0 8 97\n"
        "a=rtpmap:0 PCMU/8000\n"
        "a=rtpmap:8 PCMA/8000\n"
        "a=rtpmap:97 iLBC/8000\n"
        "m=video 51372 RTP/AVP 31 32\n"
        "a=rtpmap:31 H261/90000\n"
        "a=rtpmap:32 MPV/90000\n"
    };
    verify(expected);
}

TEST_CASE("Test 4") {
    const std::string expected{
        "v=0\n"
        "o=bob 2808844564 2808844564 IN IP4 host.biloxi.example.com\n"
        "s=Foo Bar Baz Que\n"
        "c=IN IP4 host.biloxi.example.com\n"
        "t=0 0\n"
        "m=audio 49174 RTP/AVP 0\n"
        "a=rtpmap:0 PCMU/8000\n"
        "m=video 49170 RTP/AVP 32\n"
        "a=rtpmap:32 MPV/90000\n"
    };
    verify(expected);
}

TEST_CASE("Test 5") {
    const std::string expected{
        "v=0\n"
        "o=alice 2890844526 2890844527 IN IP4 host.atlanta.example.com\n"
        "s=Foo\n"
        "c=IN IP4 host.atlanta.example.com\n"
        "t=0 0\n"
        "m=audio 51372 RTP/AVP 0\n"
        "a=rtpmap:0 PCMU/8000\n"
        "m=video 0 RTP/AVP 31\n"
        "a=rtpmap:31 H261/90000\n"
    };
    verify(expected);
}

TEST_CASE("Test 6") {
    const std::string expected{
        "v=0\n"
        "o=bob 2808844564 2808844565 IN IP4 host.biloxi.example.com\n"
        "s=Foo\n"
        "c=IN IP4 host.biloxi.example.com\n"
        "t=0 0\n"
        "m=audio 49172 RTP/AVP 0\n"
        "a=rtpmap:0 PCMU/8000\n"
        "m=video 0 RTP/AVP 31\n"
        "a=rtpmap:31 H261/90000\n"
    };
    verify(expected);
}

TEST_CASE("Test 7") {
    const std::string expected{
        "v=0\n"
        "o=alice 2890844526 2890844526 IN IP4 host.atlanta.example.com\n"
        "s=Foo\n"
        "c=IN IP4 host.atlanta.example.com\n"
        "t=0 0\n"
        "m=audio 49170 RTP/AVP 0 8 97\n"
        "a=rtpmap:0 PCMU/8000\n"
        "a=rtpmap:8 PCMA/8000\n"
        "a=rtpmap:97 iLBC/8000\n"
        "m=video 51372 RTP/AVP 31 32\n"
        "a=rtpmap:31 H261/90000\n"
        "a=rtpmap:32 MPV/90000\n"
    };
    verify(expected);
}

TEST_CASE("Test 8") {
    const std::string expected{
        "v=0\n"
        "o=bob 2808844564 2808844564 IN IP4 host.biloxi.example.com\n"
        "s=Foo\n"
        "c=IN IP4 host.biloxi.example.com\n"
        "t=0 0\n"
        "m=audio 49172 RTP/AVP 99\n"
        "a=rtpmap:99 iLBC/8000\n"
        "m=video 51374 RTP/AVP 31\n"
        "a=rtpmap:31 H261/90000\n"
    };
    verify(expected);
}

TEST_CASE("Test 9") {
    const std::string expected{
        "v=0\n"
        "o=alice 2890844526 2890844526 IN IP4 host.atlanta.example.com\n"
        "s=Foo\n"
        "c=IN IP4 host.atlanta.example.com\n"
        "t=0 0\n"
        "m=audio 49170 RTP/AVP 0 97\n"
        "a=rtpmap:0 PCMU/8000\n"
        "a=rtpmap:97 iLBC/8000\n"
        "m=audio 49172 RTP/AVP 98\n"
        "a=rtpmap:98 telephone-event/8000\n"
        "a=sendonly\n"
    };
    verify(expected);
}

TEST_CASE("Test 10") {
    const std::string expected{
        "v=0\n"
        "o=bob 2808844564 2808844564 IN IP4 host.biloxi.example.com\n"
        "s=Foo\n"
        "c=IN IP4 host.biloxi.example.com\n"
        "t=0 0\n"
        "m=audio 49172 RTP/AVP 97\n"
        "a=rtpmap:97 iLBC/8000\n"
        "m=audio 49174 RTP/AVP 98\n"
        "a=rtpmap:98 telephone-event/8000\n"
        "a=recvonly\n"
    };
    verify(expected);
}

TEST_CASE("Test 11") {
    const std::string expected{
        "v=0\n"
        "o=alice 2890844526 2890844526 IN IP4 host.atlanta.example.com\n"
        "s=Foo\n"
        "c=IN IP4 host.atlanta.example.com\n"
        "t=0 0\n"
        "m=audio 49170 RTP/AVP 97\n"
        "a=rtpmap:97 iLBC/8000\n"
        "m=video 51372 RTP/AVP 31\n"
        "a=rtpmap:31 H261/90000\n"
    };
    verify(expected);
}

TEST_CASE("Test 12") {
    const std::string expected{
        "v=0\n"
        "o=bob 2808844564 2808844564 IN IP4 host.biloxi.example.com\n"
        "s=Foo\n"
        "c=IN IP4 host.biloxi.example.com\n"
        "t=0 0\n"
        "m=audio 49174 RTP/AVP 97\n"
        "a=rtpmap:97 iLBC/8000\n"
        "m=video 49170 RTP/AVP 31\n"
        "a=rtpmap:31 H261/90000\n"
    };
    verify(expected);
}

TEST_CASE("Test 13") {
    const std::string expected{
        "v=0\n"
        "o=alice 2890844526 2890844526 IN IP4 host.atlanta.example.com\n"
        "s=Foo\n"
        "c=IN IP4 host.atlanta.example.com\n"
        "t=0 0\n"
        "m=audio 49170 RTP/AVP 0 97\n"
        "a=rtpmap:0 PCMU/8000\n"
        "a=rtpmap:97 iLBC/8000\n"
        "m=audio 49172 RTP/AVP 98\n"
        "a=rtpmap:98 telephone-event/8000\n"
        "a=sendonly\n"
    };
    verify(expected);
}

TEST_CASE("Test 14") {
    const std::string expected{
        "v=0\n"
        "o=alice 2890844526 2890844526 IN IP4 host.atlanta.example.com\n"
        "s=Foo\n"
        "c=IN IP4 host.atlanta.example.com\n"
        "t=0 0\n"
        "m=audio 49170 RTP/AVP 0 97\n"
        "a=rtpmap:0 PCMU/8000\n"
        "a=rtpmap:97 iLBC/8000\n"
    };
    verify(expected);
}

void verify(const std::string &expected) {
    sdp::SessionDescription sd;
    std::stringstream in{expected};
    REQUIRE(sdp::parse(in, &sd));

    std::stringstream out;
    sdp::generate(&sd, out);

    REQUIRE(expected.compare(out.str()) == 0);
}
