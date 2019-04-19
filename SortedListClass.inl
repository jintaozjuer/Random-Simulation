template< class T >
SortedListClass< T >::SortedListClass()
{
  head = 0;
  tail = 0;
}

template< class T >
SortedListClass< T >::SortedListClass(const SortedListClass< T > &rhs)
{
  if (rhs.head == 0 && rhs.tail == 0)
  {
    head = 0;
    tail = 0;
  }
  else
  {
    LinkedNodeClass< T > *copyPos = rhs.tail;
    LinkedNodeClass< T > *temp;
    temp = new LinkedNodeClass< T >(0, copyPos->getValue(), 0);
    head = temp;
    tail = temp;
    copyPos = copyPos->getPrev();
    while (copyPos != 0)
    {
      temp = new LinkedNodeClass< T >(0, copyPos->getValue(), temp);
      temp->setBeforeAndAfterPointers();
      head = temp;
      copyPos = copyPos->getPrev();
    }
  }
}

template< class T >
void SortedListClass< T >::clear()
{
  LinkedNodeClass< T > *clearPos;
  clearPos = head;

  while (clearPos != 0)
  {
    clearPos->setPreviousPointerToNull();
    if (clearPos->getNext() != 0)
    {
      clearPos = clearPos->getNext();
      clearPos->getPrev()->setNextPointerToNull();
      delete clearPos->getPrev();
    }
    else
    {
      delete clearPos;
      clearPos = 0;
    }
  }

  head = 0;
  tail = 0;
}

template< class T >
void SortedListClass< T >::insertValue(const T &valToInsert)
{
  LinkedNodeClass< T > *temp;

  if (head == 0 && tail == 0)
  {
    temp = new LinkedNodeClass< T >(0, valToInsert, 0);
    head = temp;
    tail = temp;
  }
  else
  {
    LinkedNodeClass< T > *insertPos;
    insertPos = head;
    bool foundInsertPlacement = false;

    while (!foundInsertPlacement && insertPos != 0)
    {
      if (valToInsert >= insertPos->getValue())
      {
        insertPos = insertPos->getNext();
      }
      else
      {
        foundInsertPlacement = true;
      }
    }

    if (insertPos == 0)
    {
      temp = new LinkedNodeClass< T >(tail, valToInsert, 0);
      tail = temp;
    }
    else
    {
      if (insertPos->getPrev() == 0)
      {
        temp = new LinkedNodeClass< T >(0, valToInsert, insertPos);
        head = temp;
      }
      else
      {
        temp = new LinkedNodeClass< T >(insertPos->getPrev(),
          valToInsert,
          insertPos);
      }
    }
    temp->setBeforeAndAfterPointers();

  }
}

template< class T >
void SortedListClass< T >::printForward() const
{
  cout << "Forward List Contents Follow:" << endl;

  LinkedNodeClass< T > *printPos;
  printPos = head;
  while (printPos != 0)
  {
    cout << "  " << printPos->getValue() << endl;
    printPos = printPos->getNext();
  }

  cout << "End Of List Contents" << endl;
}

template< class T >
void SortedListClass< T >::printBackward() const
{
  cout << "Backward List Contents Follow:" << endl;

  LinkedNodeClass< T > *printPos;
  printPos = tail;
  while (printPos != 0)
  {
    cout << "  " << printPos->getValue() << endl;
    printPos = printPos->getPrev();
  }

  cout << "End Of List Contents" << endl;
}

template< class T >
bool SortedListClass< T >::removeFront(T &theVal)
{
  bool notEmpty = true;
  if (head == 0 && tail == 0)
  {
    notEmpty = false;
  }
  else
  {
    theVal = head->getValue();
    if (head->getNext() == 0)
    {
      clear();
    }
    else
    {
      head = head->getNext();
      head->getPrev()->setNextPointerToNull();
      delete head->getPrev();
      head->setPreviousPointerToNull();
    }
  }

  return(notEmpty);
}

template< class T >
bool SortedListClass< T >::removeLast(T &theVal)
{
  bool notEmpty = true;
  if (head == 0 && tail == 0)
  {
    notEmpty = false;
  }
  else
  {
    theVal = tail->getValue();
    if (tail->getPrev() == 0)
    {
      clear();
    }
    else
    {
      tail = tail->getPrev();
      tail->getNext()->setPreviousPointerToNull();
      delete tail->getNext();
      tail->setNextPointerToNull();
    }
  }

  return(notEmpty);
}

template< class T >
int SortedListClass< T >::getNumElems() const
{
  int numOfNode = 0;
  LinkedNodeClass< T > *indexTemp = head;
  while (indexTemp != 0)
  {
    indexTemp = indexTemp->getNext();
    numOfNode++;
  }
  return(numOfNode);
}

template< class T >
bool SortedListClass< T >::getElemAtIndex(const int index, T &outVal) 
{
  bool found = true;
  LinkedNodeClass< T > *indexTemp = head;

  if (indexTemp == 0)
  {
    found = false;
  }
  else if (index < 0 || index >= getNumElems())
  {
    found = false;
  }
  else
  {
    for (int i = 0; i < index; i++)
    {
      indexTemp = indexTemp->getNext();
    }
    outVal = indexTemp->getValue();
  }

  return(found);
}

template< class T >
SortedListClass< T >::~SortedListClass()
{
  clear();
}

