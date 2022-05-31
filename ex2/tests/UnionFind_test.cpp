#include "../UnionFind.h"
#include "gtest/gtest.h"

TEST(MemoryTest, NoMemoryLeaks)
{
    UnionFind uf(4);
}

TEST(GetValueTest, FourCompanies)
{
    UnionFind uf(4);
    EXPECT_NO_FATAL_FAILURE(uf.Union(uf.Find(3), uf.Find(4), 0.5));
    EXPECT_EQ(uf.getCompanyValue(4), 5.5);
    EXPECT_EQ(uf.getCompanyValue(3), 3);
    EXPECT_NO_FATAL_FAILURE(uf.Union(uf.Find(3), uf.Find(2), 0.2));
    EXPECT_EQ(uf.getCompanyValue(4), 5.5);
    EXPECT_EQ(uf.getCompanyValue(3), 3);
    EXPECT_EQ(uf.getCompanyValue(2), 3.1);
    EXPECT_NO_FATAL_FAILURE(uf.Union(uf.Find(1), uf.Find(4), 0.5));
    EXPECT_EQ(uf.getCompanyValue(4), 6);
    EXPECT_EQ(uf.getCompanyValue(3), 3.5);
    EXPECT_EQ(uf.getCompanyValue(2), 3.6);
    EXPECT_EQ(uf.getCompanyValue(1), 1);
    EXPECT_EQ(uf.Find(1), 2);
    EXPECT_EQ(uf.Find(2), 2);
    EXPECT_EQ(uf.Find(3), 2);
    EXPECT_EQ(uf.Find(4), 2);
}

TEST(FindTest, FourCompanies)
{
    UnionFind uf(4);
    EXPECT_NO_FATAL_FAILURE(uf.Union(uf.Find(3), uf.Find(4), 1)); // TV(4)=7
    EXPECT_NO_FATAL_FAILURE(uf.Union(uf.Find(1), uf.Find(2), 1)); // TV(2)=3
    EXPECT_NO_FATAL_FAILURE(uf.Union(uf.Find(1), uf.Find(4), 1)); // TV(4)=10
    EXPECT_EQ(uf.getCompanyValue(4), 10);
    EXPECT_EQ(uf.getCompanyValue(3), 6);
    EXPECT_EQ(uf.getCompanyValue(2), 3);
    EXPECT_EQ(uf.getCompanyValue(1), 1);
    EXPECT_EQ(uf.Find(4), 4);
    EXPECT_EQ(uf.getCompanyValue(4), 10);
    EXPECT_EQ(uf.getCompanyValue(3), 6);
    EXPECT_EQ(uf.getCompanyValue(2), 3);
    EXPECT_EQ(uf.getCompanyValue(1), 1);
}

TEST(GetValueTest, TenCompanies)
{
    UnionFind uf(10);
    EXPECT_NO_FATAL_FAILURE(uf.Union(uf.Find(9), uf.Find(4), 1));
    EXPECT_EQ(uf.getCompanyValue(8), 8);
    EXPECT_NO_FATAL_FAILURE(uf.Union(uf.Find(8), uf.Find(10), 3));
    EXPECT_NO_FATAL_FAILURE(uf.Union(uf.Find(7), uf.Find(8), 4));
    EXPECT_EQ(uf.getCompanyValue(8), 36);
    EXPECT_EQ(uf.getCompanyValue(7), 7);
    EXPECT_EQ(uf.getCompanyValue(10), 62);
    EXPECT_EQ(uf.Find(9), 4);
    EXPECT_EQ(uf.Find(8), 10);
    EXPECT_EQ(uf.Find(7), 10);
}