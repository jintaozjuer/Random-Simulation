template < class T >
FIFOQueueClass< T >::FIFOQueueClass()
{
  head = 0;
  tail = 0;
}

template < class T >
void FIFOQueueClass< T >::enqueue(const T &newItem)
{
  LinkedNodeClass< T > *temp;
  if (head == 0 && tail == 0)
  {
    temp = new LinkedNodeClass< T >(0, newItem, 0);
    head = temp;
    tail = temp;
  }
  else
  {
    temp = new LinkedNodeClass< T >(tail, newItem, 0);
    temp->setBeforeAndAfterPointers();
    tail = temp;
  }
}

template < class T >
bool FIFOQueueClass< T >::dequeue(T &outItem)
{
  bool notEmpty = true;
  if (head == 0 && tail == 0)
  {
    notEmpty = false;
  }
  else
  {
    outItem = head->getValue();
    if (head->getNext() == 0)
    {
      delete head;
      head = 0;
      tail = 0;
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

template < class T >
void FIFOQueueClass< T >::print() const
{
  LinkedNodeClass< T > *printPos;
  printPos = head;

  while (printPos != 0)
  {
    cout << printPos->getValue();
    printPos = printPos->getNext();
    if (printPos != 0)
    {
      cout << " ";
    }
  }
  cout << endl;
}

template < class T >
FIFOQueueClass< T >::~FIFOQueueClass()
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

