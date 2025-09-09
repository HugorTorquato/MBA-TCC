#include "../../../src/ProcessSourceFiles/SyntaxTrees/ClassST.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "../../../src/ProcessSourceFiles/Scanner/Token.h"
#include "/app/includes/nlohmann/json.hpp"  // https://github.com/nlohmann/json

using json = nlohmann::json;

class ClassSTTest : public ::testing::Test
{
   protected:
    LineFile DefaultLineFile{1, 2, 3, 4};
    LineFile DefaultLineFileWithFileName{1, 2, 3, 4};

   protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ClassSTTest, SimpleClassStConstructor)
{
    auto className = "SimpleClass";
    ClassST simpleClass(className);

    EXPECT_EQ(simpleClass.getClassName(), className);
    EXPECT_TRUE(simpleClass.getInherencyArray().empty());
}

TEST_F(ClassSTTest, SimpleClassSTConstructor_ReceivingToken)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    EXPECT_EQ(simpleClass.getClassName(), className);
    EXPECT_TRUE(simpleClass.getInherencyArray().empty());
}

TEST_F(ClassSTTest, SimpleClassSTConstructor_ReceivingEmptyToken)
{
    std::string className;
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);

    EXPECT_THROW(ClassST simpleClass(token), std::runtime_error);
}

TEST_F(ClassSTTest, SimpleClassSTConstructor_ReceivingInvalidToken)
{
    std::string className;
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::BANG, className, DefaultLineFile);

    EXPECT_THROW(ClassST simpleClass(token), std::runtime_error);
}

TEST_F(ClassSTTest, SimpleClassWith_UniqueInherency)
{
    auto className = "SimpleClass";
    auto baseClassName = "SimpleBaseClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    EXPECT_EQ(simpleClass.getClassName(), className);
    EXPECT_TRUE(simpleClass.getInherencyArray().empty());

    std::shared_ptr<IToken> accessBaseClass =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> tokenBaseClass =
        std::make_shared<Token>(TokenType::IDENTIFIER, baseClassName, DefaultLineFile);

    simpleClass.addInherencyToClassObject(accessBaseClass, tokenBaseClass);
    auto baseClassArray = simpleClass.getInherencyArray();
    EXPECT_FALSE(baseClassArray.empty());
    EXPECT_EQ(baseClassArray.size(), 1);
    EXPECT_EQ(baseClassArray.front().first->getLexeme(), "public");
    EXPECT_EQ(baseClassArray.front().second->getLexeme(), baseClassName);
}

TEST_F(ClassSTTest, SimpleClassWith_MultipleInherencies)
{
    auto className = "SimpleClass";
    auto baseClassName = "SimpleBaseClass";
    auto baseClassName2 = "SimpleBaseClass2";

    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    EXPECT_EQ(simpleClass.getClassName(), className);
    EXPECT_TRUE(simpleClass.getInherencyArray().empty());

    std::shared_ptr<IToken> accessBaseClass =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> tokenBaseClass =
        std::make_shared<Token>(TokenType::IDENTIFIER, baseClassName, DefaultLineFile);
    std::shared_ptr<IToken> accessBaseClass2 =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> tokenBaseClass2 =
        std::make_shared<Token>(TokenType::IDENTIFIER, baseClassName2, DefaultLineFile);

    simpleClass.addInherencyToClassObject(accessBaseClass, tokenBaseClass);
    simpleClass.addInherencyToClassObject(accessBaseClass2, tokenBaseClass2);

    auto baseClassArray = simpleClass.getInherencyArray();
    std::vector<std::string> expectedNames = {baseClassName, baseClassName2};

    EXPECT_FALSE(baseClassArray.empty());
    EXPECT_EQ(baseClassArray.size(), 2);

    for (size_t i = 0; i < baseClassArray.size(); ++i)
    {
        EXPECT_EQ(baseClassArray[i].first->getTypeEnum(), TokenType::PUBLIC);
        EXPECT_EQ(baseClassArray[i].second->getTypeEnum(), TokenType::IDENTIFIER);
        EXPECT_EQ(baseClassArray[i].second->getLexeme(), expectedNames[i]);
    }
}

TEST_F(ClassSTTest, ClassST_AddInherency_InvalidAccessType)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    std::shared_ptr<IToken> invalidAccessType =
        std::make_shared<Token>(TokenType::BANG, "invalid", DefaultLineFile);
    std::shared_ptr<IToken> baseClassToken =
        std::make_shared<Token>(TokenType::IDENTIFIER, "BaseClass", DefaultLineFile);

    EXPECT_THROW(simpleClass.addInherencyToClassObject(invalidAccessType, baseClassToken),
                 std::runtime_error);
}

TEST_F(ClassSTTest, ClassST_AddInherency_InvalidClassName)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    std::shared_ptr<IToken> accessType =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> invalidClassToken =
        std::make_shared<Token>(TokenType::BANG, "invalid", DefaultLineFile);

    EXPECT_THROW(simpleClass.addInherencyToClassObject(accessType, invalidClassToken),
                 std::runtime_error);
}

TEST_F(ClassSTTest, ClassST_AddInherency_ValidAccessTypeAndClassName)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST simpleClass(token);

    std::shared_ptr<IToken> accessType =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> classToken =
        std::make_shared<Token>(TokenType::IDENTIFIER, "BaseClass", DefaultLineFile);

    EXPECT_NO_THROW(simpleClass.addInherencyToClassObject(accessType, classToken));
}

TEST_F(ClassSTTest, GetClassToken_ReturnsCorrectToken_WithFileName)
{
    auto className = "TestClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFileWithFileName);
    ClassST classST(token);

    auto returnedToken = classST.getClassToken();
    ASSERT_NE(returnedToken, nullptr);
    EXPECT_EQ(returnedToken->getLexeme(), className);
    EXPECT_EQ(returnedToken->getTypeEnum(), TokenType::IDENTIFIER);
    EXPECT_EQ(returnedToken->getLineFile(), DefaultLineFileWithFileName.getLineFileAsString());
}

TEST_F(ClassSTTest, GetClassToken_ReturnsNullptr_WhenConstructedWithString)
{
    auto className = "TestClass";
    ClassST classST(className);

    auto returnedToken = classST.getClassToken();
    EXPECT_EQ(returnedToken, nullptr);
}

TEST_F(ClassSTTest, GetClassToken_AfterAddingInherency_WithFileName)
{
    auto className = "TestClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFileWithFileName);
    ClassST classST(token);

    std::shared_ptr<IToken> accessType =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFileWithFileName);
    std::shared_ptr<IToken> baseClassToken =
        std::make_shared<Token>(TokenType::IDENTIFIER, "BaseClass", DefaultLineFileWithFileName);

    classST.addInherencyToClassObject(accessType, baseClassToken);

    EXPECT_TRUE(classST.hasBaseClasses());

    auto returnedToken = classST.getClassToken();
    ASSERT_NE(returnedToken, nullptr);
    EXPECT_EQ(returnedToken->getLexeme(), className);
    EXPECT_EQ(returnedToken->getLineFile(), DefaultLineFileWithFileName.getLineFileAsString());
}

TEST_F(ClassSTTest, GetClassToken_LineFileIsCorrect_ForDifferentLineFile)
{
    auto className = "AnotherClass";
    LineFile customLineFile{10, 20, 30, 40};
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, customLineFile);
    ClassST classST(token);

    EXPECT_FALSE(classST.hasBaseClasses());

    auto returnedToken = classST.getClassToken();
    ASSERT_NE(returnedToken, nullptr);
    EXPECT_EQ(returnedToken->getLineFile(), customLineFile.getLineFileAsString());
}

TEST_F(ClassSTTest, SimpleClassSTConstructor_ReceivingInvalidToken_WithFileName)
{
    std::string className;
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::BANG, className, DefaultLineFileWithFileName);

    EXPECT_THROW(ClassST simpleClass(token), std::runtime_error);
}

TEST_F(ClassSTTest, SimpleClassWith_MultipleInherencies_WithFileName)
{
    auto className = "SimpleClass";
    auto baseClassName = "SimpleBaseClass";
    auto baseClassName2 = "SimpleBaseClass2";

    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFileWithFileName);
    ClassST simpleClass(token);

    EXPECT_EQ(simpleClass.getClassName(), className);
    EXPECT_TRUE(simpleClass.getInherencyArray().empty());

    std::shared_ptr<IToken> accessBaseClass =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFileWithFileName);
    std::shared_ptr<IToken> tokenBaseClass =
        std::make_shared<Token>(TokenType::IDENTIFIER, baseClassName, DefaultLineFileWithFileName);
    std::shared_ptr<IToken> accessBaseClass2 =
        std::make_shared<Token>(TokenType::PROTECTED, "protected", DefaultLineFileWithFileName);
    std::shared_ptr<IToken> tokenBaseClass2 =
        std::make_shared<Token>(TokenType::IDENTIFIER, baseClassName2, DefaultLineFileWithFileName);

    simpleClass.addInherencyToClassObject(accessBaseClass, tokenBaseClass);
    simpleClass.addInherencyToClassObject(accessBaseClass2, tokenBaseClass2);

    EXPECT_TRUE(simpleClass.hasBaseClasses());

    auto baseClassArray = simpleClass.getInherencyArray();
    EXPECT_EQ(baseClassArray.size(), 2);
    EXPECT_EQ(baseClassArray[0].first->getLexeme(), "public");
    EXPECT_EQ(baseClassArray[0].second->getLexeme(), baseClassName);
    EXPECT_EQ(baseClassArray[0].second->getLineFile(),
              DefaultLineFileWithFileName.getLineFileAsString());
    EXPECT_EQ(baseClassArray[1].first->getLexeme(), "protected");
    EXPECT_EQ(baseClassArray[1].second->getLexeme(), baseClassName2);
    EXPECT_EQ(baseClassArray[1].second->getLineFile(),
              DefaultLineFileWithFileName.getLineFileAsString());
}

TEST_F(ClassSTTest, ClassST_AddInherency_InvalidAccessType_WithFileName)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFileWithFileName);
    ClassST simpleClass(token);

    std::shared_ptr<IToken> invalidAccessType =
        std::make_shared<Token>(TokenType::BANG, "invalid", DefaultLineFileWithFileName);
    std::shared_ptr<IToken> baseClassToken =
        std::make_shared<Token>(TokenType::IDENTIFIER, "BaseClass", DefaultLineFileWithFileName);

    EXPECT_THROW(simpleClass.addInherencyToClassObject(invalidAccessType, baseClassToken),
                 std::runtime_error);
}

TEST_F(ClassSTTest, ClassST_AddInherency_InvalidClassName_WithFileName)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFileWithFileName);
    ClassST simpleClass(token);

    std::shared_ptr<IToken> accessType =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFileWithFileName);
    std::shared_ptr<IToken> invalidClassToken =
        std::make_shared<Token>(TokenType::BANG, "invalid", DefaultLineFileWithFileName);

    EXPECT_THROW(simpleClass.addInherencyToClassObject(accessType, invalidClassToken),
                 std::runtime_error);
}

TEST_F(ClassSTTest, ClassST_AddInherency_ValidAccessTypeAndClassName_WithFileName)
{
    auto className = "SimpleClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFileWithFileName);
    ClassST simpleClass(token);

    std::shared_ptr<IToken> accessType =
        std::make_shared<Token>(TokenType::PRIVATE, "private", DefaultLineFileWithFileName);
    std::shared_ptr<IToken> classToken =
        std::make_shared<Token>(TokenType::IDENTIFIER, "BaseClass", DefaultLineFileWithFileName);

    EXPECT_NO_THROW(simpleClass.addInherencyToClassObject(accessType, classToken));

    EXPECT_TRUE(simpleClass.hasBaseClasses());

    auto baseClassArray = simpleClass.getInherencyArray();
    EXPECT_EQ(baseClassArray.size(), 1);
    EXPECT_EQ(baseClassArray.front().first->getLexeme(), "private");
    EXPECT_EQ(baseClassArray.front().second->getLexeme(), "BaseClass");
    EXPECT_EQ(baseClassArray.front().second->getLineFile(),
              DefaultLineFileWithFileName.getLineFileAsString());
}

TEST_F(ClassSTTest, ExportClassWithoutInherency)
{
    // Arrange
    ClassST classST("NoBase");

    // Act
    json classInfo;
    classInfo["className"] = classST.getClassName();
    classInfo["inherency"] = json::array();

    // Assert
    EXPECT_EQ(classInfo["className"], "NoBase");
    EXPECT_TRUE(classInfo["inherency"].empty());
}

TEST_F(ClassSTTest, ExportClassWithSingleInherency)
{
    // Arrange
    std::shared_ptr<IToken> classToken =
        std::make_shared<Token>(TokenType::IDENTIFIER, "Derived", DefaultLineFile);
    ClassST classST(classToken);

    std::shared_ptr<IToken> accessToken =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> baseClassToken =
        std::make_shared<Token>(TokenType::IDENTIFIER, "Base", DefaultLineFile);

    classST.addInherencyToClassObject(accessToken, baseClassToken);

    // Act
    json inherencyArray = json::array();
    for (const auto& pair : classST.getInherencyArray())
    {
        json entry;
        entry["access"] = pair.first->getLexeme();
        entry["baseClass"] = pair.second->getLexeme();
        inherencyArray.push_back(entry);
    }

    json classInfo;
    classInfo["className"] = classST.getClassName();
    classInfo["inherency"] = inherencyArray;

    // Assert
    EXPECT_EQ(classInfo["className"], "Derived");
    ASSERT_EQ(classInfo["inherency"].size(), 1);
    EXPECT_EQ(classInfo["inherency"][0]["access"], "public");
    EXPECT_EQ(classInfo["inherency"][0]["baseClass"], "Base");
}

TEST_F(ClassSTTest, ExportClassWithMultipleInherencies)
{
    // Arrange
    std::shared_ptr<IToken> classToken =
        std::make_shared<Token>(TokenType::IDENTIFIER, "MultiDerived", DefaultLineFile);
    ClassST classST(classToken);

    std::shared_ptr<IToken> publicToken =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> protectedToken =
        std::make_shared<Token>(TokenType::PROTECTED, "protected", DefaultLineFile);

    std::shared_ptr<IToken> base1 =
        std::make_shared<Token>(TokenType::IDENTIFIER, "Base1", DefaultLineFile);
    std::shared_ptr<IToken> base2 =
        std::make_shared<Token>(TokenType::IDENTIFIER, "Base2", DefaultLineFile);

    classST.addInherencyToClassObject(publicToken, base1);
    classST.addInherencyToClassObject(protectedToken, base2);

    // Act
    json inherencyArray = json::array();
    for (const auto& pair : classST.getInherencyArray())
    {
        json entry;
        entry["access"] = pair.first->getLexeme();
        entry["baseClass"] = pair.second->getLexeme();
        inherencyArray.push_back(entry);
    }

    json classInfo;
    classInfo["className"] = classST.getClassName();
    classInfo["inherency"] = inherencyArray;

    // Assert
    EXPECT_EQ(classInfo["className"], "MultiDerived");
    ASSERT_EQ(classInfo["inherency"].size(), 2);
    EXPECT_EQ(classInfo["inherency"][0]["access"], "public");
    EXPECT_EQ(classInfo["inherency"][0]["baseClass"], "Base1");
    EXPECT_EQ(classInfo["inherency"][1]["access"], "protected");
    EXPECT_EQ(classInfo["inherency"][1]["baseClass"], "Base2");
}

TEST_F(ClassSTTest, ExportInherencyArray_ToJson)
{
    auto className = "DerivedClass";
    std::shared_ptr<IToken> token =
        std::make_shared<Token>(TokenType::IDENTIFIER, className, DefaultLineFile);
    ClassST derivedClass(token);

    // Add two base classes
    std::shared_ptr<IToken> accessBaseClass1 =
        std::make_shared<Token>(TokenType::PUBLIC, "public", DefaultLineFile);
    std::shared_ptr<IToken> tokenBaseClass1 =
        std::make_shared<Token>(TokenType::IDENTIFIER, "Base1", DefaultLineFile);

    std::shared_ptr<IToken> accessBaseClass2 =
        std::make_shared<Token>(TokenType::PROTECTED, "protected", DefaultLineFile);
    std::shared_ptr<IToken> tokenBaseClass2 =
        std::make_shared<Token>(TokenType::IDENTIFIER, "Base2", DefaultLineFile);

    derivedClass.addInherencyToClassObject(accessBaseClass1, tokenBaseClass1);
    derivedClass.addInherencyToClassObject(accessBaseClass2, tokenBaseClass2);

    // --- Convert to JSON ---
    json inherenciesJson = json::array();
    for (const auto& pair : derivedClass.getInherencyArray())
    {
        json inh;
        inh["access"] = pair.first->getLexeme();
        inh["baseClass"] = pair.second->getLexeme();
        inh["lineFile"] = pair.second->getLineFile();
        inherenciesJson.push_back(inh);
    }

    // --- Assertions ---
    ASSERT_EQ(inherenciesJson.size(), 2);

    EXPECT_EQ(inherenciesJson[0]["access"], "public");
    EXPECT_EQ(inherenciesJson[0]["baseClass"], "Base1");
    EXPECT_EQ(inherenciesJson[0]["lineFile"], DefaultLineFile.getLineFileAsString());

    EXPECT_EQ(inherenciesJson[1]["access"], "protected");
    EXPECT_EQ(inherenciesJson[1]["baseClass"], "Base2");
    EXPECT_EQ(inherenciesJson[1]["lineFile"], DefaultLineFile.getLineFileAsString());
}
