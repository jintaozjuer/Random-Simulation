template< class T >
LinkedNodeClass< T >::LinkedNodeClass(
  LinkedNodeClass *inPrev,
  const T &inVal,
  LinkedNodeClass *inNext)
{
  prevNode = inPrev;
  nodeVal = inVal;
  nextNode = inNext;
}

template< class T >
T LinkedNodeClass< T >::getValue() const
{
  return(nodeVal);
}

template< class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getNext() const
{
  return(nextNode);
}

template< class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getPrev() const
{
  return(prevNode);
}

template< class T >
void LinkedNodeClass< T >::setNextPointerToNull()
{
  nextNode = 0;
}

template< class T >
void LinkedNodeClass< T >::setPreviousPointerToNull()
{
  prevNode = 0;
}

template< class T >
void LinkedNodeClass< T >::setBeforeAndAfterPointers()
{
  if (this->prevNode != 0 && this->nextNode != 0)
  {
    this->prevNode->nextNode = this;
    this->nextNode->prevNode = this;
  }
  else if (this->prevNode == 0 && this->nextNode != 0)
  {
    this->nextNode->prevNode = this;
  }
  else if (this->prevNode != 0 && this->nextNode == 0)
  {
    this->prevNode->nextNode = this;
  }
}

