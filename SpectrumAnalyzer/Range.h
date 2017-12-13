#ifndef RANGE_H
#define RANGE_H

template <class T>
class Range {

    private:
        T max;
        T min;

    public:
        Range(T values[], int size);
        T getMax();
        T getMin();
};

template <class T>
Range<T>::Range(T values[], int size) {

    if (size <= 0) {
        max = 0;
        min = 0;
    } else {
        max = values[0];
        min = values[0];
    }

    for (int i = 1; i < size; i++) {
        if (values[i] > max) max = values[i];
        if (values[i] < min) min = values[i];
    }
}

template <class T>
T Range<T>::getMax() {
    return max;
}

template <class T>
T Range<T>::getMin() {
    return min;
}

#endif // RANGE_H

