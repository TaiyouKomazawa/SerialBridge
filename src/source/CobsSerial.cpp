#include "../CobsSerial.hpp"

#include "../cobs.hpp"

CobsSerial::CobsSerial(SerialDev *dev)
    : _rx_buffer(COBS_RX_BUFFER_SIZE)
{
    _dev = dev;
    _got_packet = false;
}

int CobsSerial::read(uint8_t *data, const unsigned int max_len)
{
    int cnt = 0;
    uint8_t tmp[max_len] = {};

    if(!_data_begin && _got_packet){
        uint8_t val = 1;
        while(_rx_buffer.size()){
            val = _rx_buffer.front();
            _rx_buffer.pop();
            tmp[cnt] = val;
            cnt++;
        }

        if(val == 0){ //データパケットの終端で終了
            _got_packet = false;
            cnt = cobsDecode(tmp, cnt, data);
        }else{
            cnt = 0;
        }
    }
    return cnt;
}

int CobsSerial::write(uint8_t *data, const unsigned int len)
{
    uint8_t tmp[COBS_TX_BUFFER_SIZE] = {};
    int tx_size = cobsEncode(data, len, tmp+1); //先頭の次にcobsコードを代入
    return _dev->write(tmp, tx_size+2);
}

void CobsSerial::update()
{
    if(_dev->readable_len()){
        char tmp = _dev->read();

        if(_data_begin && _got_packet){
            if(tmp){                    //データの始端(始端の次のデータが始端以外であるとき)
                _rx_buffer.push(tmp);
                _got_packet = false;
                return;
            }
        }

        if(!tmp){                       //データが0であったときの処理
            if(!_rx_buffer.size()){     //データが入っていないとき
                _data_begin = true;
                return;                 //フラグがtrue,trueで終了
            }else{                      //データの終端(データが入っているとき)
                _rx_buffer.push(tmp);

                _data_begin = false;
                _got_packet = true;
                return;
            }
        }

        if(_data_begin && !_got_packet){ //データの追加
            _rx_buffer.push(tmp);
        }
    }
}
