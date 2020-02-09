#include <iostream>

#define MIN(X, Y) (X < Y) ? X : Y;

struct Block {
    char sex;
    unsigned long start, end;
};

class PatientDiapasone {
    char _sex;
    unsigned long _start;
    unsigned long _end;
    unsigned long _dead_count[3];
    
public:
    
    PatientDiapasone () {
        _sex = ' ';
        _start = 0;
        _end = 0;
        _dead_count[0] = _dead_count[1] = _dead_count[2] = 0;
    }
    
    void setSex (char sex) {
        _sex = sex;
    }
    
    void setBounds (unsigned long start, unsigned long count) {
        _start = start;
        _end = start + count;
    }
    
    unsigned long start () {
        return _start;
    }
    
    unsigned long end () {
        return _end;
    }
    
    char sex () {
        return _sex;
    }
    
    bool isInDiapasone (unsigned long position) {
        return position >= _start && position <= _end;
    }
    
    void addPatients (char sex, unsigned long count) {
        switch (sex) {
            case 'c':
                _dead_count[0] += count;
                break;
                
            case 'f':
                _dead_count[1] += count;
                break;
                
            case 'm':
                _dead_count[2] += count;
                break;
                
            default:
                break;
        }
    }
    
    unsigned long children () {
        return _dead_count[0];
    }
    
    unsigned long female () {
        return _dead_count[1];
    }
    
    unsigned long male () {
        return _dead_count[2];
    }
    
    bool needToMovePatients () {
        switch (_sex) {
            case 'c':
                return _dead_count[1] != 0 || _dead_count[2] != 0;
                
            case 'f':
                return _dead_count[0] != 0 || _dead_count[2] != 0;
                
            case 'm':
                return _dead_count[0] != 0 || _dead_count[1] != 0;
                
            default:
                return false;
        }
    }
    
    void decrement (unsigned int index, unsigned long value) {
        _dead_count[index] -= value;
    }
    
    void increment (unsigned int index, unsigned long value) {
        _dead_count[index] += value;
    }
    
    unsigned long getPatients(unsigned index) {
        return _dead_count[index];
    }
};

class Mortuary {
    unsigned long _blocks_count;
    Block _bloks[1000];
    
    unsigned long _diapasones_count;
    PatientDiapasone _diapasones[3];
    
    unsigned long _total_children;
    unsigned long _total_female;
    unsigned long _total_male;
    
public:
    
    Mortuary ()
    {
        _blocks_count = 0;
        _diapasones_count = 3;
        _diapasones[0].setSex('c');
        _diapasones[1].setSex('f');
        _diapasones[2].setSex('m');
        _total_children = 0;
        _total_female = 0;
        _total_male = 0;
    }
    
    void addPatients (char sex, unsigned long count) {
        _bloks[_blocks_count].start = (_blocks_count > 0) ? _bloks[_blocks_count - 1].end : 0;
        _bloks[_blocks_count].sex = sex;
        _bloks[_blocks_count].end = _bloks[_blocks_count].start + count;
        
        switch (sex) {
            case 'c':
                _total_children += count;
                break;
                
            case 'f':
                _total_female += count;
                break;
                
            case 'm':
                _total_male += count;
                break;
                
            default:
                break;
        }
        
        _blocks_count++;
    }
    
    void calculatePatients() {
        _diapasones[0].setBounds(0, _total_children);
        _diapasones[1].setBounds(_diapasones[0].end(), _total_female);
        _diapasones[2].setBounds(_diapasones[1].end(), _total_male);
        
        for (int i = 0; i < _blocks_count; i++) {
            for (int diapasone = 0; diapasone < _diapasones_count; diapasone++) {
                
                if (_diapasones[diapasone].isInDiapasone(_bloks[i].start)) {
                    if (_diapasones[diapasone].isInDiapasone(_bloks[i].end)) {
                        _diapasones[diapasone].addPatients(_bloks[i].sex, _bloks[i].end - _bloks[i].start);
                    } else if (_bloks[i].end > _diapasones[diapasone].end()) {
                        _diapasones[diapasone].addPatients(_bloks[i].sex, _diapasones[diapasone].end() - _bloks[i].start);
                    }
                } else if (_diapasones[diapasone].isInDiapasone(_bloks[i].end)) {
                    _diapasones[diapasone].addPatients(_bloks[i].sex, _bloks[i].end - _diapasones[diapasone].start());
                } else if (_bloks[i].start < _diapasones[diapasone].start() && _bloks[i].end > _diapasones[diapasone].end()) {
                    _diapasones[diapasone].addPatients(_bloks[i].sex, _diapasones[diapasone].end() - _diapasones[diapasone].start());
                }
            }
        }
        
        //        debug_info();
    }
    
    unsigned long patientCountToMove () {
        unsigned long movedPatients = 0;
        
        while (_diapasones[0].needToMovePatients() || _diapasones[1].needToMovePatients() || _diapasones[2].needToMovePatients()) {
            
            bool needMoveDirectPatients = false;
            do {
                needMoveDirectPatients = false;
                
                for (unsigned i = 0; i < 3; i++) {
                    unsigned next = (i + 1) > 2 ? 0 : i + 1;
                    
                    if (_diapasones[i].getPatients(next) > 0 && _diapasones[next].getPatients(i) > 0) {
                        unsigned long countToMove = MIN(_diapasones[i].getPatients(next), _diapasones[next].getPatients(i));
                        _diapasones[i].decrement(next, countToMove);
                        _diapasones[i].increment(i, countToMove);
                        _diapasones[next].decrement(i, countToMove);
                        _diapasones[next].increment(next, countToMove);
                        movedPatients += countToMove;
                        needMoveDirectPatients = true;
                    }
                }
            } while (needMoveDirectPatients);
            
            //            debug_info();
            
            unsigned diapasone_index, main_index, additional_index = 0;
            unsigned long max_count = 0;
            for (unsigned i = 0; i < 3; i++) {
                for (unsigned j = 0; j < 3; j++) {
                    if (i != j) {
                        if (max_count < _diapasones[i].getPatients(j)) {
                            
                            for (unsigned n = 0; n < 3; n++) {
                                if (n != i && n != j && _diapasones[i].getPatients(j) == _diapasones[j].getPatients(n)) {
                                    max_count = _diapasones[i].getPatients(j);
                                    diapasone_index = i;
                                    main_index = j;
                                    additional_index = n;
                                }
                            }
                        }
                    }
                }
            }
            
            if (max_count > 0) {
                unsigned long countToMove = _diapasones[diapasone_index].getPatients(main_index);
                
                _diapasones[diapasone_index].decrement(main_index, countToMove);
                _diapasones[diapasone_index].increment(additional_index, countToMove);
                
                
                _diapasones[main_index].decrement(additional_index, countToMove);
                _diapasones[main_index].increment(main_index, countToMove);
                
                movedPatients += countToMove;
            }
            
            //            debug_info();
        }
        
        return movedPatients;
    }
    
    void debug_info () {
        std::cout << _diapasones[0].children() << " " << _diapasones[0].female() << " " << _diapasones[0].male() << std::endl;
        std::cout << _diapasones[1].children() << " " << _diapasones[1].female() << " " << _diapasones[1].male() << std::endl;
        std::cout << _diapasones[2].children() << " " << _diapasones[2].female() << " " << _diapasones[2].male() << std::endl;
    }
    
};

int main ()
{
    Mortuary mortuary;
    unsigned long blocks_count;
    char block_sex = ' ';
    int block_count = 0;
    
    std::cin >> blocks_count;
    
    for (int i = 0; i < blocks_count; i++) {
        std::cin >> block_sex;
        std::cin >> block_count;
        
        mortuary.addPatients(block_sex, block_count);
    }
    
    mortuary.calculatePatients();
    
    std::cout << mortuary.patientCountToMove() << std::endl;
    
	return 0;
}