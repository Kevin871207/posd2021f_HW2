#include "../src/article.h"
#include "../src/list_item.h"
#include "../src/paragraph.h"
#include "../src/text.h"

TEST(CaseParagraph, Creation) {
  ASSERT_NO_THROW(Paragraph p(1, "title"));
}

TEST(CaseParagraph, ParagraphShouldBeAArticle) {
  Article* p = new Paragraph(2, "title2");
  ASSERT_TRUE(typeid(p) == typeid(Article*));
}

TEST(CaseParagraph, LevelIsZero) {
  ASSERT_ANY_THROW(Paragraph p(0, "title"));
}

TEST(CaseParagraph, LevelIsNegative) {
  ASSERT_ANY_THROW(Paragraph p(-5, "title"));
}

TEST(CaseParagraph, LevelIsLargerThenSix) {
  ASSERT_ANY_THROW(Paragraph p(7, "title"));
}

TEST(CaseParagraph, GetText) {
  Paragraph p(1, "title");
  ASSERT_EQ("# title\n", p.getText());
}

TEST(CaseParagraph, GetLevel) {
  Paragraph p(1, "title");
  ASSERT_EQ(1, p.getLevel());
}

TEST(CaseParagraph, AddLowerOrEqualLevelParagraphShouldThrow) {
  Paragraph p(3, "title");
  Paragraph* p2 = new Paragraph(2, "title2");
  ASSERT_ANY_THROW(p.add(p2));
}

TEST(CaseParagraph, GetTextWithContent) {
  Paragraph p(1, "title");
  p.add(new ListItem("list1"));
  p.add(new ListItem("list2"));
  p.add(new Text("text"));
  ASSERT_EQ("# title\n- list1\n- list2\ntext",
    p.getText());
}

TEST(CaseParagraph, GetTextWithComplexContent) {
  Paragraph p(1, "title");
  p.add(new ListItem("list1"));
  p.add(new ListItem("list2"));
  p.add(new Text("text"));
  Paragraph* p2 = new Paragraph(2, "title2");
  p2->add(new ListItem("list3"));
  p2->add(new ListItem("list4"));
  p2->add(new Text("sub text"));
  p.add(p2);
  ASSERT_EQ("# title\n- list1\n- list2\ntext\n## title2\n- list3\n- list4\nsub text", p.getText());
}
