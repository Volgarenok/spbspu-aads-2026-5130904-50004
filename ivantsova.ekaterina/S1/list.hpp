#ifndef LIST_HPP
#define LIST_HPP

namespace ivantsova
{
  template< class T > class List;

  template< class T > class LIter
  {
    friend class List< T >;

  public:

  private:
  };

  template< class T > class LCIter
  {
    friend class ivantsova::List< T >;

  public:

  private:
  };

  template< class T > class List
  {
    friend class LIter< T >;
    friend class LCIter< T >;

  private:

  public:

  };
}

#endif
