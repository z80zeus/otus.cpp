#define BOOST_TEST_MODULE publisherCommandsFromStream

#include "../src/commandBlockFiler.h"
#include "../src/commandBlockPrinter.h"
#include "../src/publisherCommandsFromStream.h"
#include "../src/subscriber.h"

#include <boost/test/unit_test.hpp>

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct dummySubscriber: z80::subscriber<std::string> {
  dummySubscriber(vector<string>& dest): dst(dest) {};

  virtual void update(const string& str) {
    dst.push_back(str);
  }

  virtual void unsubscribed() {
    dst.push_back("unsubscribed");
  };
  vector<string>& dst;
};

BOOST_AUTO_TEST_SUITE(test_PCFS)
  BOOST_AUTO_TEST_CASE(test_create_pcfs) {
    istringstream is;
    BOOST_CHECK_NO_THROW((z80::publisherCommandsFromStream(is)));
  }

  BOOST_AUTO_TEST_CASE(test_pass_string) {
    vector<string>  src { "1", "2", "3", "4" };
    vector<string>  dst;
    string          srcStr;
    for(auto str : src) srcStr += str + "\n";
    istringstream is(srcStr.c_str());
    dummySubscriber subscriber(dst);
    z80::publisherCommandsFromStream publisher(is);
    publisher.subscribe(subscriber);
    publisher.start();
    BOOST_CHECK_EQUAL(dst.at(dst.size()-1), "unsubscribed");
    dst.pop_back();
    BOOST_CHECK_EQUAL(src == dst, true);
  }

  BOOST_AUTO_TEST_CASE(test_printer_string) {
    string src { "bulk: 1, 2, 3, 4" };  // "bulk: " играет роль unixtime, которое появится в выводе парсера команд.
    ostringstream os;
    z80::commandBlockPrinter printer(os);
    printer.update(src);
    BOOST_CHECK_EQUAL(os.str(), src + "\n");
  }

  BOOST_AUTO_TEST_CASE(test_filer_string) {
    string filename {"unixtime"};
    string src { "1, 2, 3, 4" };
    ostringstream os;
    z80::commandBlockFiler filer;
    filer.update(filename + " " + src);
    ifstream iFile("bulk"+filename+".log");
    string dst;
    getline(iFile, dst);
    BOOST_CHECK_EQUAL(src, dst);
  }
}
