
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "logotype.c"

// mode_input = 0; // cli
// mode_input = 1; // arg
// mode_input = 2; // file
int mode_input = 2;

int skip_separators = 1;

char in_str[1000];
char tmp_str[1000];
char out_str[1000];

int count_c = 0;
int count_s = 0;
int n = 0;

size_t tmp_i = 0;
size_t out_i = 0;

int sentence_end = 0;

int logger_init(void)
{
    FILE *log_file = fopen("program.log", "r");

    if (log_file == NULL)
    {
        return 1;
    }

    fclose(log_file);
    return 0;
}

int logger(const char message[])
{
    FILE *log_file = fopen("program.log", "a");

    if (log_file == NULL)
    {
        return 1;
    }

    if (fprintf(log_file, "%s\n", message) < 0)
    {
        fclose(log_file);
        return 1;
    }

    if (fclose(log_file) == EOF)
    {
        return 1;
    }

    return 0;
}

void logger_message(const char format[], ...)
{
    char message[1000];
    char final_message[1100];
    char time_string[30];

    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);

    time_t now = time(NULL);
    struct tm *time_info = localtime(&now);

    strftime(time_string, sizeof(time_string),
             "%Y-%m-%d %H:%M:%S", time_info);

    snprintf(final_message, sizeof(final_message),
             "[%s] %s", time_string, message);

    if (logger(final_message) != 0)
    {
        printf("Критическая ошибка: не удалось записать сообщение в program.log!\n");
        printf("\nНажмите Enter!\n");
        getchar();
        exit(1);
    }
}

void the_end(void)
{
    printf("\nНажмите Enter!\n");
    getchar();
    logger_message("Программа завершила работу");
    exit(0);
}

void write_to_out_str(const char *mode)
{
    if (strcmp(mode, "default") == 0)
    {
        for (size_t j = 0; j < tmp_i; j++)
        {
            out_str[out_i] = tmp_str[j];
            out_i++;
        }
    }
    else if (strcmp(mode, "mod") == 0)
    {
        out_str[out_i] = '*';
        out_i++;
    }
}

void clean_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int main(int argc, char *argv[])
{
    logo();
    printf("\nОписание программы: все предложения длиннее N символов заменить символом '*'\n\n");

    if (logger_init() == 1)
    {
        printf("\nОшибка! Не найден файл program.log\n");
        printf("Создайте файл program.log в текущей рабочей директории (папке)\n");
        printf("После запустите программу ещё раз\n");
        printf("\nНажмите Enter!\n");
        getchar();
        exit(0);
    }

    logger_message("Программа запустилась");

    // mode_input 0 cli
    if (mode_input == 0)
    {
        printf("Введите число N:\n");
        printf("Допустимое значение: положительное целое число\n");
        printf("Пример ввода: 5\n");

        if (scanf("%d", &n) != 1)
        {
            printf("Ошибка: не получилось прочитать N!\n");
            logger_message("Ошибка чтения N");
            clean_stdin();
            the_end();
        }

        clean_stdin();

        if (n <= 0)
        {
            printf("Ошибка: введите целое число больше 0!\n");
            logger_message("Введено некорректное значение N");
            the_end();
        }

        logger_message("Получено значение N = %d", n);

        printf("Границы предложений определяются символами '.', '!' и '?'.\n");
        printf("Если предложение последнее или единственное в тексте, оно учитывается даже без завершающего знака препинания.\n");
        printf("Длина предложения включает все символы(вкл пробелы и знаки препинания.)\n\n");
        printf("Пример: Привет мир! Cуслик это ты?\n");
        printf("Введите текст:\n");

        if (fgets(in_str, sizeof(in_str), stdin) == NULL)
        {
            printf("Ошибка: не получилось прочитать текст!\n");
            logger_message("Ошибка чтения текста");
            the_end();
        }

        logger_message("Текст получен из терминала");
    }

    // mode_input 1 arg
    else if (mode_input == 1)
    {
        if (argc < 3)
        {
            printf("Ошибка: недостаточно аргументов!\n");
            printf("Используйте: %s <N> <текст>\n", argv[0]);
            printf("\nГраницы предложений определяются символами '.', '!' и '?'.\n");
            printf("Если предложение последнее или единственное в тексте, оно учитывается даже без завершающего знака препинания.\n");
            printf("Длина предложения включает все символы(вкл пробелы и знаки препинания)\n\n");
            printf("Пример: %s 10 Привет мир! Cуслик это ты?\n", argv[0]);
            logger_message("Недостаточно аргументов командной строки");
            the_end();
        }

        n = atoi(argv[1]);

        if (n <= 0)
        {
            printf("Ошибка: N должно быть целым числом больше 0!\n");
            logger_message("Введено некорректное значение N");
            the_end();
        }

        logger_message("Получено значение N = %d", n);

        // Объединяем argv[2] и послед арг
        in_str[0] = '\0';

        for (int i = 2; i < argc; i++)
        {
            size_t current_length = strlen(in_str);
            size_t argument_length = strlen(argv[i]);
            size_t space_length = (i > 2) ? 1 : 0;

            if (current_length + space_length + argument_length >= sizeof(in_str))
            {
                printf("Ошибка: текст превышает допустимую длину!\n");
                logger_message("Превышена допустимая длина текста");
                the_end();
            }

            if (i > 2)
            {
                strcat(in_str, " ");
            }

            strcat(in_str, argv[i]);
        }

        logger_message("Текст получен из аргументов командной строки");
    }

    // input_mode 2 file
    else if (mode_input == 2)
    {
        if (argc < 3)
        {
            printf("Ошибка: недостаточно аргументов!\n");
            printf("Используй: %s <N> <путь к файлу>\n", argv[0]);
            printf("\n<N>: положительное целое число\n");
            printf("Пример <N>: 5\n");
            printf("Путь к файлу может быть абсолютным или относительным.\n");
            printf("\nГраницы предложений определяются символами '.', '!' и '?'.\n");
            printf("Если предложение последнее или единственное в тексте, оно учитывается даже без завершающего знака препинания.\n");
            printf("Длина предложения включает все символы(вкл пробелы и знаки препинания)\n\n");
            printf("Пример: %s 10 ./input.txt\n", argv[0]);
            logger_message("Недостаточно аргументов командной строки");
            the_end();
        }

        n = atoi(argv[1]);

        if (n <= 0)
        {
            printf("Ошибка: N должно быть целым числом больше 0!\n");
            logger_message("Введено некорректное значение N");
            the_end();
        }

        logger_message("Получено значение N = %d", n);

        FILE *input_file = fopen(argv[2], "r");

        if (input_file == NULL)
        {
            printf("Ошибка: не удалось открыть файл %s\n", argv[2]);
            logger_message("Не удалось открыть входной файл: %s", argv[2]);
            the_end();
        }

        size_t bytes_read = fread(in_str, 1, sizeof(in_str) - 1, input_file);

        if (ferror(input_file))
        {
            printf("Ошибка чтения файла!\n");
            logger_message("Ошибка чтения файла: %s", argv[2]);
            fclose(input_file);
            the_end();
        }

        in_str[bytes_read] = '\0';

        if (fclose(input_file) == EOF)
        {
            printf("Ошибка закрытия входного файла!\n");
            logger_message("Ошибка закрытия входного файла: %s", argv[2]);
            the_end();
        }

        if (bytes_read == 0)
        {
            printf("Ошибка: входной файл пуст!\n");
            logger_message("Входной файл пуст");
            the_end();
        }

        logger_message("Текст получен из файла: %s", argv[2]);
    }

    else
    {
        printf("Ошибка: неизвестный режим ввода!\n");
        logger_message("Неизвестный режим ввода: %d", mode_input);
        the_end();
    }

    // Подготовка текста к обработке
    size_t length = strlen(in_str);

    if (length > 0 && in_str[length - 1] == '\n')
    {
        in_str[length - 1] = '\0';
        length--;
    }

    // Обработка предложений
    for (size_t i = 0; i < length; i++)
    {
        // Запись предложения
        if (sentence_end == 1 &&
            in_str[i] != '.' &&
            in_str[i] != '!' &&
            in_str[i] != '?')
        {
            if (n < count_c)
            {
                count_s++;
                write_to_out_str("mod");
            }
            else
            {
                write_to_out_str("default");
            }

            count_c = 0;
            sentence_end = 0;
            tmp_i = 0;
        }
        // Первый знак окончания
        if (in_str[i] == '.' ||
            in_str[i] == '!' ||
            in_str[i] == '?')
        {
            sentence_end = 1;
        }

        // Пропуск разделителей
        if ((in_str[i] == ' ' ||
             in_str[i] == '\t' ||
             in_str[i] == '\r' ||
             in_str[i] == '\n') &&
            count_c == 0 &&
            skip_separators == 0)
        {
            out_str[out_i] = in_str[i];
            out_i++;
            continue;
        }

        unsigned char c = (unsigned char)in_str[i];

        // Проверка начального байта
        if ((c & 0xC0) != 0x80)
        {
            count_c++;
        }

        tmp_str[tmp_i] = in_str[i];
        tmp_i++;
    }

    // запись последнего предложения
    if (count_c > 0)
    {
        if (count_c > n)
        {
            count_s++;
            write_to_out_str("mod");
        }
        else
        {
            write_to_out_str("default");
        }

        tmp_i = 0;
    }

    out_str[out_i] = '\0';

    logger_message("Преобразовано %d предложений", count_s);

    // Экспорт результата
    FILE *output_file = fopen("result.txt", "w");

    if (output_file == NULL)
    {
        printf("\nНе удалось открыть/создать файл для экспорта\n");
        logger_message("Не удалось открыть/создать файл для экспорта");
        the_end();
    }

    if (fprintf(output_file, "%s\n", out_str) < 0)
    {
        printf("Ошибка записи результата в файл!\n");
        logger_message("Ошибка записи в result.txt");
        fclose(output_file);
        the_end();
    }

    if (fclose(output_file) == EOF)
    {
        printf("Ошибка закрытия файла result.txt!\n");
        logger_message("Ошибка закрытия файла result.txt");
        the_end();
    }

    logger_message("Результат записан в файл result.txt");

    printf("\nИзначальный текст: %s\n", in_str);
    printf("\nПреобразованный текст: %s\n", out_str);
    printf("\nРезультат записан в файл result.txt\n");

    the_end();
}
