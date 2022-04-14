#include "gtest/gtest.h"
#include "search.h"


std::vector <BasePoint> fillTestBasePoints() {
    BasePoint a, b, c, d;
    Edge edge;
    a.id = 1;
    // base
    edge = {2, 2, "1->2.txt"};
    a.BasePointEdges.push_back(edge);
    edge = {4, 1, "1->4.txt"};
    a.BasePointEdges.push_back(edge);
    // infr
    edge = {9, 5, "1->9.txt"};
    a.InfrastructureEdges.push_back(edge);
    edge = {10, 2, "1->10.txt"};
    a.InfrastructureEdges.push_back(edge);
    edge = {11, 2, "1->11.txt"};
    a.InfrastructureEdges.push_back(edge);


    b.id = 2;
    // base
    edge = {1, 2, "2->1.txt"};
    b.BasePointEdges.push_back(edge);
    edge = {3, 5, "2->3.txt"};
    b.BasePointEdges.push_back(edge);
    // infr
    edge = {10, 0, "2->10.txt"};
    b.InfrastructureEdges.push_back(edge);
    edge = {11, 1, "2->11.txt"};
    b.InfrastructureEdges.push_back(edge);
    edge = {12, 2, "2->12.txt"};
    b.InfrastructureEdges.push_back(edge);
    edge = {13, 3, "2->13.txt"};
    b.InfrastructureEdges.push_back(edge);

    c.id = 3;
    // base
    edge = {2, 5, "3->2.txt"};
    c.BasePointEdges.push_back(edge);
    edge = {4, 2, "3->4.txt"};
    c.BasePointEdges.push_back(edge);
    // infr
    edge = {12, 1, "3->12.txt"};
    c.InfrastructureEdges.push_back(edge);
    edge = {13, 1, "3->13.txt"};
    c.InfrastructureEdges.push_back(edge);

    d.id = 4;
    // base
    edge = {1, 1, "4->1.txt"};
    d.BasePointEdges.push_back(edge);
    edge = {3, 2, "4->3.txt"};
    d.BasePointEdges.push_back(edge);

    std::vector <BasePoint> graf = {a, b, c, d};
    return graf;
}

std::vector <Infrastructure> fillInfrPoints() {
    Infrastructure i9, i10, i11, i12, i13;
    Edge edge;
    i9.id = 9;
    i9.name = "399u";
    edge = {1, 5, "9->1.txt"};
    i9.BasePointEdges.push_back(edge);

    i10.id = 10;
    i10.name = "400u";
    edge = {1, 2, "10->1.txt"};
    i10.BasePointEdges.push_back(edge);
    edge = {2, 0, "10->2.txt"};
    i10.BasePointEdges.push_back(edge);

    i11.id = 11;
    i11.name = "401u";
    edge = {1, 2, "11->1.txt"};
    i11.BasePointEdges.push_back(edge);
    edge = {2, 1, "11->2.txt"};
    i11.BasePointEdges.push_back(edge);

    i12.id = 12;
    i12.name = "402u";
    edge = {2, 2, "12->2.txt"};
    i12.BasePointEdges.push_back(edge);
    edge = {3, 1, "12->3.txt"};
    i12.BasePointEdges.push_back(edge);

    i13.id = 13;
    i13.name = "403u";
    edge = {2, 2, "13->2.txt"};
    i13.BasePointEdges.push_back(edge);
    edge = {3, 1, "13->3.txt"};
    i13.BasePointEdges.push_back(edge);

    std::vector <Infrastructure> graf = {i9, i10, i11, i12, i13};
    return graf;
}


class DataBaseTest : public DataBase {
public:
    std::vector <BasePoint> getBasePoints() override {
        return fillTestBasePoints();
    }
    std::vector <Infrastructure> getInfrastructurePoints() override {
        return fillInfrPoints();
    }
};



TEST(Func, testCi) {
    DataBaseTest data;
    Search s1(&data);
    std::vector <std::string> foundRoute = s1.FindRoute("399u", "403u");
    EXPECT_EQ(foundRoute.size(), 4);
    EXPECT_EQ(foundRoute[0], "9->1.txt");
    EXPECT_EQ(foundRoute[1], "1->4.txt");
    EXPECT_EQ(foundRoute[2], "4->3.txt");
    EXPECT_EQ(foundRoute[3], "3->13.txt");
    {
        std::vector <std::string> foundRoute = s1.FindRoute("401u", "403u");
        assert(foundRoute.size() == 2);
        assert(foundRoute[0] == "11->2.txt");
        assert(foundRoute[1] == "2->13.txt");
    }
    {
        std::vector <std::string> foundRoute = s1.FindRoute("401u", "401u");
        assert(foundRoute.size() == 0);
    }
    {
        std::vector <std::string> foundRoute;
        bool wasException = false;
        try {
            s1.FindRoute("cant find object", "401u");
        } catch (Search::Exeptions exception) {
            assert(exception == Search::Exeptions::UNKNOWN_POINT);
            wasException = true;
        }
        assert(wasException == true);
        assert(foundRoute.size() == 0);
    }
}