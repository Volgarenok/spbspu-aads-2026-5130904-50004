#include "expressions_processing.h"

alekseev::Queue< alekseev::List< char > * > alekseev::stoq(std::string str_expr)
{
  Queue< List< char > * > res;
  size_t i = 0;
  while (i < str_expr.size()) {
    char current_char = str_expr[i++];
    List< char > * cur_fake = nullptr;
    try {
      cur_fake = fake< char >();
      List< char > * cur_tail = cur_fake;
      while (current_char != ' ' && i < str_expr.size()) {
        cur_tail = insert_after(cur_tail, current_char);
        current_char = str_expr[i++];
      }
      res.push(cur_fake);
    } catch (...) {
      clear(cur_fake->next, cur_fake);
      rmfake(cur_fake);
      while (!res.empty()) {
        List< char > * tmp = res.front();
        res.pop();
        clear(tmp->next, tmp);
        rmfake(tmp);
      }
      throw;
    }
  }
  return res;
}
