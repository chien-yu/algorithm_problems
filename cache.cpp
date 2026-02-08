#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>

using namespace std;

class LFUCache {
public:
    unordered_map<int, int> keyToValue;
    unordered_map<int, int> keyToFreq;
    map<int, int> freqToKey;
    int capacity;
    LFUCache(int capacity_) {
        capacity = capacity_;
    }
    
    int get(int key) {
        if (keyToValue.count(key) == 0)
        {
            return -1;
        }
        // update freq
        int freq = keyToFreq[key];
        freqToKey.erase(freq);
        freqToKey.insert(make_pair(freq+1, key));
        keyToFreq[key]++;
        cout << "get. key " << key << " freq is " << keyToFreq[key] << endl;

        return keyToValue[key];
    }
    
    void put(int key, int value) {
        if (keyToValue.count(key))
        {
            // update
            keyToValue[key] = value;
            // update freq
            // but how to find out the key in freqToKey, which key is freq
            int freq = keyToFreq[key];
            freqToKey.erase(freq);
            freqToKey.insert(make_pair(freq+1, key));
            keyToFreq[key]++;
        }
        else
        {
            // new key
            cout << "key " << key << " not exist\n";
            if (keyToValue.size() == capacity)
            {
                // remove LFU
                int keyToRemove = freqToKey.rbegin()->second;
                cout << "remove key: " << keyToRemove <<endl;
                for (auto& p : freqToKey)
                {
                    cout << "key " << p.first << " value " << p.second << endl;
                }
                freqToKey.erase(freqToKey.begin());
                keyToFreq.erase(keyToRemove);
                keyToValue.erase(keyToRemove);
            }
            keyToValue[key] = value;
            freqToKey.insert(freqToKey.begin(), make_pair(1, key));
            cout << "size of freqToKey " << freqToKey.size() << endl;
            keyToFreq.insert(make_pair(key, 1));
        }
        cout << "put. key " << key << " freq is " << keyToFreq[key] << endl;
        for (auto& p : freqToKey)
        {
            cout << "freqToKey freq " << p.first << " key " << p.second << endl;
        }
    }
};

int main()
{
    
}