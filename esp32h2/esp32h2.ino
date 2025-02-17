typedef struct __Status
{
    gpio_num_t pin_no;
    int status;
} Status;

#define IO_NUM 15

Status statuses[IO_NUM] = {
    {GPIO_NUM_0, 0},
    {GPIO_NUM_1, 0},
    {GPIO_NUM_2, 0},
    {GPIO_NUM_3, 0},
    {GPIO_NUM_4, 0},
    {GPIO_NUM_5, 0},
    {GPIO_NUM_8, 0},
    {GPIO_NUM_9, 0},
    {GPIO_NUM_10, 0},
    {GPIO_NUM_11, 0},
    {GPIO_NUM_12, 0},
    // {GPIO_NUM_13, 0}, XTAL_32K_P
    // {GPIO_NUM_14, 0}, XTAL_32K_N
    {GPIO_NUM_22, 0},
    {GPIO_NUM_23, 0},
    {GPIO_NUM_24, 0},
    {GPIO_NUM_25, 0},
    // {GPIO_NUM_26, 0}, D-
    // {GPIO_NUM_27, 0}, D+
};

void setup()
{
    Serial.begin(115200);
    for (int i = 0; i < IO_NUM; i++)
    {
        pinMode(statuses[i].pin_no, INPUT_PULLUP);
        statuses[i].status = digitalRead(statuses[i].pin_no);
    }
    Serial.println("init");
}

void loop()
{
    for (int i = 0; i < IO_NUM; i++)
    {
        int r = digitalRead(statuses[i].pin_no);
        if (r != statuses[i].status)
        {
            statuses[i].status = r;
            if (r == 0)
            {
                Serial.printf("%d L\r\n", statuses[i].pin_no);
            }
            else
            {
                Serial.printf("%d H\r\n", statuses[i].pin_no);
            }
        }
    }

    char buf[256];
    int n = Serial.read(buf, 256);
    if (n > 0)
    {
        Serial.printf("RX: %s\r\n", buf);
    }

    delay(100);
}