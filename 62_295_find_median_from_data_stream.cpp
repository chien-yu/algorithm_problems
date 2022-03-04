// old
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        slots = vector<vector<int>>(201, vector<int>());
        num = 0;
    }
    
    void addNum(int num) {
        // make slot first
        // 200 slot, each contains 100 numbers
        //
        // 0-99 -> 0 -> 100
        // -10000 -> -100 -> 0
        // -9999 -> -99
        // 10000 -> 100 -> 200
        int slotIdx = num/100 + 100;
        slot[slotIdx].push_back(num);
        num++;
    }
    
    double findMedian() {
        // find the num/2 slot
        int count = 0;
        int i = 0;
        bool bEven = false;
        if (num % 2)
        {
            // odd, median is on (num+1)/2
            // 3 -> on index 1
        }
        else
        {
            // even, median is between (num/2 - 1) and num/2
            // 4 -> betwwen 1 & 2
            bEven = true;
        }
        for (; i <= 201; i++)
        {
            count += slots[i].size();
            if (bEven)
            {
                // between (num/2 - 1) and num/2
                if (count >= num/2 - 1)
                    break;
            }
            else
            {
                if (count >= (num+1)/2)
                    break;
            }
        }
        // median in slot[i]
        if (bEven)
        {
            
        }
        else
        {
            
        }
        return 0;
    }
    vector<vector<int>> slots;
    int num;
};

// second try, good.
class MedianFinder {
public:
    MedianFinder() {
        // 2, 10000 => 5001. add 5000 (< 5001)
        // 2, 5000, 10000
        // 10, 20, 30, 40, 50, 60 => avg 35. add 20
        // {       30}{40          }
        // 2 priority queue?
        MIN_INT = numeric_limits<int>::min();
        mid = MIN_INT;
    }
    
    void addNum(int num) {
        // always add to left, and we can normalize
        if (left.size() == 0 && right.size() == 0)
        {
            if (mid == MIN_INT)
                mid = num;
            else
            {
                right.push(max(num,mid));
                left.push(min(num,mid));
                mid = MIN_INT;
            }
            return;
        }
        // make sure at least one
        //  A    B
        // ^   ^   ^
        if (left.top() >= num)
        {
            left.push(num);
            if (mid != MIN_INT)
            {
                right.push(mid);
                mid = MIN_INT;
            }
            else
            {
                mid = left.top();
                left.pop();
            }
        }
        else if (right.top() <= num)
        {
            right.push(num);
            if (mid != MIN_INT)
            {
                left.push(mid);
                mid = MIN_INT;
            }
            else
            {
                mid = right.top();
                right.pop();
            }
        }
        else
        {
            // in the middle
            if (mid != MIN_INT)
            {
                right.push(max(num,mid));
                left.push(min(num,mid));
                mid = MIN_INT;
            }
            else
            {
                mid = num;
            }
        }
    }
    
    double findMedian() {
        // cout << mid << endl;
        if (mid != MIN_INT)
            return mid;
        // assume size always the same
        // if (left.size() == right.size())
        return (left.top() + right.top()) / 2.0;
        // else if (left.size() + 1 == right.size())
        //     return left.top();
        // else if (left.size() == right.size() + 1)
        //     return right.top();
    }
    
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;
    int mid;
    int MIN_INT;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */