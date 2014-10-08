using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NosebleedStudios.Utilities
{
    

    public abstract class ReadOnlyListCpp<T>: IEnumerable<T>
    {
        protected abstract IEnumerator<T> GetEnumeratorImpl();
        protected abstract T GetItemByIndex(int index);

        public T this[int index]
        {
            get { return GetItemByIndex(index); }
        }

        public IEnumerator<T> GetEnumerator()
        {
            return GetEnumeratorImpl();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumeratorImpl();
        }

        public abstract int Count { get; }

    }
}
