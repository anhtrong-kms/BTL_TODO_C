#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NO_TASKS 100

// Khai báo kiểu enum CommandType

    COMPLETED,
    IN_PROGRESS,
    REMOVED
} Status;

// Khai báo kiểu cấu trúc Task
struct Task {
    char title[100];
    char description[500];
    char time[20];
    int num;
    enum Status status;
};

//Định nghĩa các hàm

CommandType getCommandType(char *command) {
    /**
     * \brief Xác định kiểu lệnh từ chuỗi lệnh được truyền vào.
     *
     * Hàm này nhận vào một chuỗi command chứa một lệnh và xác định kiểu lệnh tương ứng.
     *
     * \param command (char*): Chuỗi chứa một lệnh.
     *
     * \return Kiểu lệnh tương ứng với lệnh được truyền vào.
     *         Nếu lệnh không hợp lệ, trả về giá trị INVALID.
     */
    char *validCommands[] = {"Add", "Edit", "Show", "Delete", "Quit"};
    char *w = strtok(command, " ");
    
    for (int i = 0; i < 5; i++) {
        if (strcmp(w, validCommands[i]) == 0) {
            return i;
        }
    }

    return INVALID;
}

// TODO: YÊU CẦU 2 - Hiện thực 3 hàm: getTitleFromAdd, getDescriptionFromAdd, getTimeFromAdd

void getTitleFromAdd(char *command, char *out_title) {
    /**
     * \brief Lấy tiêu đề từ chuỗi lệnh Add.
     *
     * Hàm này nhận vào một chuỗi command chứa lệnh Add và trích xuất tiêu đề từ đó.
     *
     * \param command (char*): Chuỗi chứa lệnh Add.
     * \param out_title (char*): Con trỏ tới vùng nhớ để lưu trữ tiêu đề.
     */
    // Tìm vị trí bắt đầu của tiêu đề (ký tự '[')
    char *titleStart = strchr(command, '[');
    if (titleStart != NULL) {
        titleStart++;  // Bỏ qua ký tự '['
        
        // Tìm vị trí kết thúc của tiêu đề (ký tự ']')
        char *titleEnd = strchr(titleStart, ']');
        if (titleEnd != NULL) {
            // Sao chép tiêu đề vào out_title và đảm bảo kết thúc chuỗi
            strncpy(out_title, titleStart, titleEnd - titleStart);
            out_title[titleEnd - titleStart] = '\0';
        }
    }
}

void getDescriptionFromAdd(char *command, char *out_description) {
    /**
     * \brief Lấy mô tả từ chuỗi lệnh Add.
     *
     * Hàm này nhận vào một chuỗi command chứa lệnh Add và trích xuất mô tả từ đó.
     *
     * \param command (char*): Chuỗi chứa lệnh Add.
     * \param out_description (char*): Con trỏ tới vùng nhớ để lưu trữ mô tả.
     */
    // Tìm vị trí kết thúc của tiêu đề (ký tự ']')
    char *titleEnd = strchr(command, ']');
    if (titleEnd != NULL) {
        titleEnd++;  // Bỏ qua ký tự ']'
        
        // Tìm vị trí bắt đầu của mô tả (ký tự '[')
        char *descStart = strchr(titleEnd, '[');
        if (descStart != NULL) {
            descStart++;  // Bỏ qua ký tự '['
            
            // Tìm vị trí kết thúc của mô tả (ký tự ']')
            char *descEnd = strchr(descStart, ']');
            if (descEnd != NULL) {
                // Sao chép mô tả vào out_description và đảm bảo kết thúc chuỗi
                strncpy(out_description, descStart, descEnd - descStart);
                out_description[descEnd - descStart] = '\0';
            }
        }
    }
}

void getTimeFromAdd(char *command, char *out_time) {
    /**
     * \brief Trích xuất thời gian từ câu lệnh "Add".
     *
     * Hàm này nhận vào một chuỗi command chứa câu lệnh "Add" và trích xuất thời gian từ đó.
     * Nếu thời gian được tìm thấy, nó sẽ được sao chép vào chuỗi out_time.
     *
     * \param command (char*): Chuỗi chứa câu lệnh "Add".
     * \param out_time (char*): Chuỗi chứa thời gian được trích xuất.
     */
    // Tìm vị trí kết thúc của tiêu đề
    char *descEnd = strchr(command, ']');
    if (descEnd != NULL) {
        descEnd++; // Bỏ qua ký tự ']' và di chuyển đến tiếp theo
        // Tìm vị trí bắt đầu của thời gian
        char *timeStart = strchr(descEnd, '[');
        if (timeStart != NULL) {
            timeStart++; // Bỏ qua ký tự '[' và di chuyển đến tiếp theo
            // Tìm vị trí kết thúc của thời gian
            char *timeEnd = strchr(timeStart, ']');
            if (timeEnd != NULL) {
                // Sao chép thời gian vào chuỗi out_time
                strncpy(out_time, timeStart, timeEnd - timeStart);
                out_time[timeEnd - timeStart] = '\0'; // Đảm bảo kết thúc chuỗi
            }
        }
    }
}

// TODO: YÊU CẦU 3 - hiện thực hàm checkTitle

int checkTitle(char *raw_title) {
    /**
     * \brief Kiểm tra tính hợp lệ của tiêu đề.
     *
     * Hàm này kiểm tra tính hợp lệ của tiêu đề được truyền vào.
     * Tiêu đề hợp lệ phải thỏa các điều kiện sau:
     * 1. Độ dài không vượt quá MAX_TITLE_LENGTH.
     * 2. Không chứa ký tự đặc biệt như '[' hoặc ']'.
     *
     * \param raw_title (char*): Chuỗi chứa tiêu đề cần kiểm tra.
     *
     * \return Nếu tiêu đề là hợp lệ trả về -1.
     *         Nếu tiêu đề không hợp lệ do vượt quá độ dài tối đa, trả về độ dài hiện tại của tiêu đề.
     *         Nếu tiêu đề không hợp lệ do chứa ký tự đặc biệt, trả về vị trí của ký tự đầu tiên vi phạm điều kiện.
     */
    int len = strlen(raw_title);
    if (len > MAX_TITLE_LENGTH) {
        return len;
    }

    for (int i = 0; i < len; i++) {
        if (raw_title[i] == '[' || raw_title[i] == ']') {
            return i;
        }
    }

    return -1;
}

// TODO: YÊU CẦU 4 - Hiện thực hàm checkDescription

int checkDescription(char *raw_description) {
    /**
     * \brief Kiểm tra tính hợp lệ của mô tả.
     *
     * Hàm này kiểm tra tính hợp lệ của mô tả dựa trên các điều kiện sau:
     * 1. Độ dài mô tả không vượt quá MAX_DESCRIPTION_LENGTH ký tự.
     *
     * \param raw_description (char*): Chuỗi chứa mô tả cần kiểm tra.
     *
     * \return -1 nếu mô tả hợp lệ.
     *         Nếu mô tả không hợp lệ do vượt quá độ dài tối đa,
     *         trả về độ dài hiện tại của mô tả.
     *         Nếu mô tả không hợp lệ do vi phạm các điều kiện khác
     *         (ngoài độ dài tối đa), trả về vị trí của ký tự đầu tiên vi phạm điều kiện.
     */
    // Kiểm tra độ dài mô tả
    int desc_length = strlen(raw_description);
    if (desc_length > MAX_DESCRIPTION_LENGTH) {
        return desc_length;
    }
    
    return -1; // Mô tả hợp lệ
}

// TODO: YÊU CẦU 5 - Hiện thực hàm checkTime

int checkTime(char *raw_time) {
    /**
     * \brief Kiểm tra tính hợp lệ của thời gian.
     *
     * Hàm này kiểm tra tính hợp lệ của thời gian dựa trên các điều kiện sau:
     * 1. Thời gian phải có định dạng "hh:mm yyyy/mm/dd".
     * 2. <hh> phải là số từ 00 đến 23.
     * 3. <mm> phải là số từ 00 đến 59.
     * 4. <yyyy> phải là số dương.
     * 5. <mo> phải là số từ 01 đến 12.
     * 6. <dd> phải là số từ 01 đến 31.
     *
     * \param raw_time (char*): Chuỗi chứa thời gian cần kiểm tra.
     *
     * \return -1 nếu thời gian hợp lệ.
     *         Nếu thời gian không hợp lệ do vi phạm điều kiện 3, trả về 0.
     *         Nếu thời gian không hợp lệ do vi phạm các điều kiện còn lại,
     *         trả về giá trị như sau:
     *         1100+<hh> nếu <hh> không hợp lệ.
     *         1200+<hh> nếu <hh> không hợp lệ.
     *         2100+<mm> nếu <mm> không hợp lệ.
     *         2200+<mm> nếu <mm> không hợp lệ.
     *         3100+<dd> nếu <dd> không hợp lệ.
     *         3200+<dd> nếu <dd> không hợp lệ.
     *         4100+<mo> nếu <mo> không hợp lệ.
     *         4200+<mo> nếu <mo> không hợp lệ.
     *         510000+<yyyy> nếu <yyyy> không hợp lệ.
     *         520000+<yyyy> nếu <yyyy> không hợp lệ.
     */
    
    // Tách các thành phần thời gian
    int hh, mm, yyyy, mo, dd;
    if (sscanf(raw_time, "%02d:%02d %04d/%02d/%02d", &hh, &mm, &yyyy, &mo, &dd) != 5) {
        return 0; // Định dạng không đúng
    }
    
    // Kiểm tra giờ
    if (hh < 0 || hh > 23) {
        return 1100 + hh;
    }
    
    // Kiểm tra phút
    if (mm < 0 || mm > 59) {
        return 2100 + mm;
    }
    
    // Kiểm tra năm
    if (yyyy <= 0) {
        return 510000 + yyyy;
    }
    
    // Kiểm tra tháng
    if (mo < 1 || mo > 12) {
        return 4100 + mo;
    }
    
    // Kiểm tra ngày
    if (dd < 1 || dd > 31) {
        return 3100 + dd;
    }
    
    return -1; // Thời gian hợp lệ
}

//TODO: YÊU CẦU 6 - Hiện thực 3 hàm: getTitleFromEdit, getDescriptionFromEdit, getTimeFromEdit

void getTitleFromEdit(char *command, char *out_title) {
    /**
     * \brief Trích xuất tiêu đề từ câu lệnh "Edit".
     *
     * Hàm này nhận vào một chuỗi command chứa câu lệnh "Edit" và trích xuất tiêu đề từ đó.
     * Nếu tiêu đề được tìm thấy, nó sẽ được sao chép vào chuỗi out_title.
     *
     * \param command (char*): Chuỗi chứa câu lệnh "Edit".
     * \param out_title (char*): Chuỗi chứa tiêu đề được trích xuất.
     */

    // Tìm vị trí bắt đầu của tiêu đề bằng cách tìm ký tự '[' đầu tiên
    char *titleStart = strchr(command, '[');

    // Nếu tìm thấy '['
    if (titleStart != NULL) {
        titleStart++; // Di chuyển con trỏ lên để bỏ qua ký tự '['
        char *titleEnd = strchr(titleStart, ']'); // Tìm ký tự ']' kế tiếp

        // Nếu tìm thấy ký tự ']'
        if (titleEnd != NULL) {
            // Sao chép tiêu đề từ titleStart đến titleEnd vào out_title
            strncpy(out_title, titleStart, titleEnd - titleStart);
            out_title[titleEnd - titleStart] = '\0'; // Đảm bảo chuỗi kết thúc bằng null character
        }
    }
}

void getDescriptionFromEdit(char *command, char *out_description) {
    /**
     * \brief Trích xuất mô tả từ câu lệnh "Edit".
     *
     * Hàm này nhận vào một chuỗi command chứa câu lệnh "Edit" và trích xuất mô tả từ đó.
     * Nếu mô tả được tìm thấy, nó sẽ được sao chép vào chuỗi out_description.
     *
     * \param command (char*): Chuỗi chứa câu lệnh "Edit".
     * \param out_description (char*): Chuỗi chứa mô tả được trích xuất.
     */

    // Tìm vị trí kết thúc của tiêu đề (ký tự ']') để bắt đầu tìm mô tả
    char *titleEnd = strchr(command, ']');

    // Nếu tìm thấy ký tự ']', tiếp tục tìm ký tự '[' để xác định mô tả
    if (titleEnd != NULL) {
        titleEnd++; // Di chuyển con trỏ lên để bỏ qua ký tự ']'
        char *descStart = strchr(titleEnd, '['); // Tìm ký tự '[' kế tiếp

        // Nếu tìm thấy ký tự '['
        if (descStart != NULL) {
            descStart++; // Di chuyển con trỏ lên để bỏ qua ký tự '['
            char *descEnd = strchr(descStart, ']'); // Tìm ký tự ']' tiếp theo

            // Nếu tìm thấy ký tự ']'
            if (descEnd != NULL) {
                // Sao chép mô tả từ descStart đến descEnd vào out_description
                strncpy(out_description, descStart, descEnd - descStart);
                out_description[descEnd - descStart] = '\0'; // Đảm bảo chuỗi kết thúc bằng null character
            }
        }
    }
}

void getTimeFromEdit(char *command, char *out_time) {
    /**
     * \brief Trích xuất thời gian từ câu lệnh "Edit".
     *
     * Hàm này nhận vào một chuỗi command chứa câu lệnh "Edit" và trích xuất thời gian từ đó.
     * Nếu thời gian được tìm thấy, nó sẽ được sao chép vào chuỗi out_time.
     *
     * \param command (char*): Chuỗi chứa câu lệnh "Edit".
     * \param out_time (char*): Chuỗi chứa thời gian được trích xuất.
     */

    // Tìm vị trí kết thúc của mô tả (ký tự ']') để bắt đầu tìm thời gian
    char *descEnd = strchr(command, ']');

    // Nếu tìm thấy ký tự ']', tiếp tục tìm ký tự '[' để xác định mô tả
    if (descEnd != NULL) {
        descEnd++; // Di chuyển con trỏ lên để bỏ qua ký tự ']'
        char *timeStart = strchr(descEnd, '['); // Tìm ký tự '[' kế tiếp

        // Nếu tìm thấy ký tự '['
        if (timeStart != NULL) {
            timeStart++; // Di chuyển con trỏ lên để bỏ qua ký tự '['
            char *timeEnd = strchr(timeStart, ']'); // Tìm ký tự ']' tiếp theo

            // Nếu tìm thấy ký tự ']'
            if (timeEnd != NULL) {
                // Sao chép thời gian từ timeStart đến timeEnd vào out_time
                strncpy(out_time, timeStart, timeEnd - timeStart);
                out_time[timeEnd - timeStart] = '\0'; // Đảm bảo chuỗi kết thúc bằng null character
            }
        }
    }
}

// TODO: YÊU CẦU 7 - Hiện thực hàm getNumFromCommand

int getNumFromCommand(char *command) {
    /**
     * \brief Trích xuất số từ câu lệnh.
     *
     * Hàm này nhận vào một chuỗi command chứa một câu lệnh và trích xuất số từ đó.
     * Số được trích xuất được trả về. Nếu không tìm thấy số, hàm sẽ trả về -1.
     *
     * \param command (char*): Chuỗi chứa một câu lệnh.
     *
     * \return Số được trích xuất. Nếu không tìm thấy số, trả về -1.
     */

    char *numStart = strchr(command, '#'); // Tìm ký tự '#' đầu tiên

    // Nếu tìm thấy ký tự '#'
    if (numStart != NULL) {
        numStart++; // Di chuyển con trỏ lên để bỏ qua ký tự '#'
        int num = atoi(numStart); // Chuyển đổi chuỗi thành số nguyên

        return num;
    }

    return -1; // Trả về -1 nếu không tìm thấy số
}

//TODO: YÊU CẦU 8 - Hiện thực hàm getFieldFromEdit

int getFieldFromEdit(char *edit_cmd) {
    /**
     * \brief Xác định trường cần chỉnh sửa từ câu lệnh "Edit".
     *
     * Hàm này nhận vào một chuỗi edit_cmd chứa câu lệnh "Edit" và xác định trường cần chỉnh sửa.
     * Trường cần chỉnh sửa được xác định dựa trên các từ khóa (title, description, time, status)
     * trong câu lệnh. Nếu không tìm thấy trường cần chỉnh sửa, hàm sẽ trả về 0.
     *
     * \param edit_cmd (char*): Chuỗi chứa câu lệnh "Edit".
     *
     * \return Trường cần chỉnh sửa. Nếu không tìm thấy, trả về 0.
     */
    
    if (strstr(edit_cmd, "title") != NULL) {
        return 1; // Chỉnh sửa tiêu đề
    } else if (strstr(edit_cmd, "description") != NULL) {
        return 2; // Chỉnh sửa mô tả
    } else if (strstr(edit_cmd, "time") != NULL) {
        return 3; // Chỉnh sửa thời gian
    } else if (strstr(edit_cmd, "status") != NULL) {
        return 4; // Chỉnh sửa trạng thái
    }

    return 0; // Không tìm thấy trường cần chỉnh sửa
}

// TODO: YÊU CẦU 9 - Hiện thực hàm getStatusFromEdit

enum Status getStatusFromEdit(char *edit_cmd) {
    /**
     * \brief Xác định trạng thái từ câu lệnh "Edit".
     *
     * Hàm này nhận vào một chuỗi edit_cmd chứa câu lệnh "Edit" và xác định trạng thái được
     * chỉnh sửa trong câu lệnh. Trạng thái được xác định dựa trên các từ khóa (done, pending)
     * trong câu lệnh. Nếu không tìm thấy trạng thái, hàm sẽ trả về NOT_SET.
     *
     * \param edit_cmd (char*): Chuỗi chứa câu lệnh "Edit".
     *
     * \return Trạng thái được chỉnh sửa. Nếu không tìm thấy, trả về NOT_SET.
     */
    
    if (strstr(edit_cmd, "done") != NULL) {
        return DONE;
    } else if (strstr(edit_cmd, "pending") != NULL) {
        return PENDING;
    }

    return NOT_SET; // Không tìm thấy trạng thái
}

//TODO: YÊU CẦU 10 - Hiện thực hàm printAllTasks

void printAllTasks(struct Task *array_tasks, int no_tasks) {
    /**
     * \brief In ra tất cả các công việc trong mảng.
     *
     * Hàm này nhận vào một mảng các công việc và số lượng công việc trong mảng,
     * sau đó in ra thông tin của từng công việc.
     *
     * \param array_tasks (struct Task*): Mảng chứa các công việc.
     * \param no_tasks (int): Số lượng công việc trong mảng.
     */
    for (int i = 0; i < no_tasks; i++) {
        printTask(array_tasks[i]);
    }
}

//TODO: YÊU CẦU 11 - Hiện thực hàm printTaskByNum

void printTaskByNum(struct Task *array_tasks, int no_tasks, int num) {
    /**
     * \brief In ra thông tin của công việc có số thứ tự num.
     *
     * Hàm này nhận vào một mảng các công việc, số lượng công việc trong mảng,
     * và số thứ tự num. Sau đó in ra thông tin của công việc có số thứ tự num nếu có.
     * Nếu không tìm thấy công việc tương ứng, in ra thông báo lỗi.
     *
     * \param array_tasks (struct Task*): Mảng chứa các công việc.
     * \param no_tasks (int): Số lượng công việc trong mảng.
     * \param num (int): Số thứ tự của công việc cần in.
     */
    for (int i = 0; i < no_tasks; i++) {
        if (array_tasks[i].num == num) {
            printTask(array_tasks[i]);
            return;
        }
    }
    printf("Khong tim thay cong viec voi so thu tu %d.\n", num);
}

//TODO: YÊU CẦU 12 - Hiện thực hàm printHeadTasks

void printHeadTasks(struct Task *array_tasks, int no_tasks, int quan) {
    /**
     * \brief In ra quan công việc đầu tiên trong mảng array_task.
     *
     * Hàm này nhận vào một mảng các công việc, số lượng công việc trong mảng, và
     * số lượng công việc cần in (quan). Sau đó in ra quan công việc đầu tiên trong mảng
     * array_task. Nếu mảng có ít hơn quan công việc, in ra toàn bộ mảng.
     *
     * \param array_tasks (struct Task*): Mảng chứa các công việc.
     * \param no_tasks (int): Số lượng công việc trong mảng.
     * \param quan (int): Số lượng công việc cần in.
     */
    int i;
    for (i = 0; i < no_tasks && i < quan; i++) {
        printTask(array_tasks[i]);
    }
    if (i == 0) {
        printf("Khong co cong viec nao de hien thi.\n");
    }
}

//TODO: YÊU CẦU 13 - Hiện thực hàm printTailTasks

void printTailTasks(struct Task *array_tasks, int no_tasks, int quan) {
    /**
     * \brief In ra quan công việc cuối cùng trong mảng array_task.
     *
     * Hàm này nhận vào một mảng các công việc, số lượng công việc trong mảng, và
     * số lượng công việc cần in (quan). Sau đó in ra quan công việc cuối cùng trong mảng
     * array_task. Nếu mảng có ít hơn quan công việc, in ra toàn bộ mảng.
     *
     * \param array_tasks (struct Task*): Mảng chứa các công việc.
     * \param no_tasks (int): Số lượng công việc trong mảng.
     * \param quan (int): Số lượng công việc cần in.
     */
    int i;
    if (no_tasks <= quan) {
        for (i = 0; i < no_tasks; i++) {
            printTask(array_tasks[i]);
        }
    } else {
        for (i = no_tasks - quan; i < no_tasks; i++) {
            printTask(array_tasks[i]);
        }
    }
    if (i == 0) {
        printf("Khong co cong viec nao de hien thi.\n");
    }
}

//TODO: YÊU CẦU 14 - Hiện thực hàm printFilteredTasksByTitle

void printFilteredTasksByTitle(struct Task *array_tasks, int no_tasks, char *filter_title) {
    /**
     * \brief In ra các công việc trong mảng array_task có filter_title là một chuỗi con
     *        của biến thành viên title.
     *
     * Hàm này nhận vào một mảng các công việc, số lượng công việc trong mảng, và
     * một chuỗi filter_title. Sau đó in ra các công việc trong mảng array_task có
     * filter_title là một chuỗi con của biến thành viên title, sử dụng hàm printTask khi
     * in mỗi công việc.
     *
     * \param array_tasks (struct Task*): Mảng chứa các công việc.
     * \param no_tasks (int): Số lượng công việc trong mảng.
     * \param filter_title (char*): Chuỗi cần lọc.
     */
    int i, found = 0;
    for (i = 0; i < no_tasks; i++) {
        if (strstr(array_tasks[i].title, filter_title) != NULL) {
            printTask(array_tasks[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong co cong viec nao phu hop.\n");
    }
}

//TODO: YÊU CẦU 15 - Hiện thực hàm printFilteredTasksByDescription

void printFilteredTasksByDescription(struct Task *array_tasks, int no_tasks, char *filter_description) {
    /**
     * \brief In ra các công việc trong mảng array_task có filter_description là một chuỗi con
     *        của biến thành viên description.
     *
     * Hàm này nhận vào một mảng các công việc, số lượng công việc trong mảng, và
     * một chuỗi filter_description. Sau đó in ra các công việc trong mảng array_task có
     * filter_description là một chuỗi con của biến thành viên description, sử dụng hàm
     * printTask khi in mỗi công việc.
     *
     * \param array_tasks (struct Task*): Mảng chứa các công việc.
     * \param no_tasks (int): Số lượng công việc trong mảng.
     * \param filter_description (char*): Chuỗi cần lọc.
     */
    int i, found = 0;
    for (i = 0; i < no_tasks; i++) {
        if (strstr(array_tasks[i].description, filter_description) != NULL) {
            printTask(array_tasks[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong co cong viec nao phu hop.\n");
    }
}

//TODO: YÊU CẦU 16 - Hiện thực hàm printFilteredTasksByStatus

void printFilteredTasksByStatus(struct Task *array_tasks, int no_tasks, enum Status filter_status) {
    /**
     * \brief In ra các công việc trong mảng array_task có giá trị của biến thành viên status trùng
     *        với giá trị của filter_status.
     *
     * Hàm này nhận vào một mảng các công việc, số lượng công việc trong mảng, và một enum filter_status.
     * Sau đó in ra các công việc trong mảng array_task có giá trị của biến thành viên status trùng
     * với giá trị của filter_status, sử dụng hàm printTask khi in mỗi công việc.
     *
     * \param array_tasks (struct Task*): Mảng chứa các công việc.
     * \param no_tasks (int): Số lượng công việc trong mảng.
     * \param filter_status (enum Status): Trạng thái cần lọc.
     */
    int i, found = 0;
    for (i = 0; i < no_tasks; i++) {
        if (array_tasks[i].status == filter_status) {
            printTask(array_tasks[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong co cong viec nao phu hop.\n");
    }
}

//TODO: YÊU CẦU 17 - Hiện thực hàm addTask

bool addTask(struct Task *array_tasks, int *no_tasks, char *new_title, char *new_description, char *new_time) {
    /**
     * \brief Thêm một công việc mới vào mảng công việc.
     *
     * Hàm này thêm một công việc mới vào mảng công việc. Nếu việc thêm thành công,
     * số lượng công việc trong mảng sẽ được cập nhật.
     *
     * \param array_tasks (struct Task*): Mảng chứa các công việc.
     * \param no_tasks (int*): Con trỏ tới số lượng công việc trong mảng.
     * \param new_title (char*): Tiêu đề của công việc mới.
     * \param new_description (char*): Mô tả của công việc mới.
     * \param new_time (char*): Thời gian của công việc mới.
     *
     * \return Trả về giá trị true nếu việc thêm công việc thành công, ngược lại trả về false.
     */
    if (*no_tasks >= MAX_NO_TASKS) {
        return false; // Không thể thêm công việc mới nếu mảng đã đầy
    }

    struct Task new_task;

    // Gán các trường thông tin cho công việc mới
    new_task.num = *no_tasks + 1; // Số công việc được tăng lên mỗi khi thêm mới
    strncpy(new_task.title, new_title, MAX_TITLE_LENGTH);
    strncpy(new_task.description, new_description, MAX_DESCRIPTION_LENGTH);
    strncpy(new_task.time, new_time, MAX_TIME_LENGTH);
    new_task.status = NOT_COMPLETED;

    array_tasks[*no_tasks] = new_task; // Thêm công việc vào cuối mảng
    (*no_tasks)++; // Cập nhật số lượng công việc

    return true;
}

//TODO: YÊU CẦU 18 - Hiện thực hàm deleteTask

bool deleteTask(struct Task *array_tasks, int *no_tasks, int num) {
    /**
     * \brief Xóa công việc có số thứ tự num khỏi mảng công việc.
     *
     * Hàm này xóa công việc có số thứ tự num khỏi mảng công việc. Nếu việc xóa thành công,
     * số lượng công việc trong mảng sẽ được cập nhật.
     *
     * \param array_tasks (struct Task*): Mảng chứa các công việc.
     * \param no_tasks (int*): Con trỏ tới số lượng công việc trong mảng.
     * \param num (int): Số thứ tự của công việc cần xóa.
     *
     * \return Trả về giá trị true nếu việc xóa công việc thành công, ngược lại trả về false.
     */
    if (num < 1 || num > *no_tasks) {
        return false; // Số thứ tự không hợp lệ
    }

    // Dịch các công việc phía sau công việc bị xóa lên trên
    for (int i = num - 1; i < *no_tasks - 1; i++) {
        array_tasks[i] = array_tasks[i + 1];
    }

    (*no_tasks)--; // Giảm số lượng công việc

    return true;
}

//TODO: YÊU CẦU 19 - Hiện thực hàm printWeekTime

int printWeekTime(struct Task *array_tasks, int no_tasks, char *date) {
    /**
     * \brief Hiển thị công việc trong tuần dựa trên ngày được cung cấp.
     *
     * Hàm này hiển thị các công việc trong tuần dựa trên ngày được cung cấp trong chuỗi date.
     * Nếu không thể hiển thị công việc theo tuần, nó sẽ trả về vị trí của công việc đầu tiên
     * gây ra lỗi không thể hiển thị theo tuần.
     *
     * \param array_tasks (struct Task*): Mảng chứa các công việc.
     * \param no_tasks (int): Số lượng công việc trong mảng.
     * \param date (char*): Chuỗi chứa thông tin về thứ, ngày, tháng, năm.
     *
     * \return Trả về giá trị -1 nếu có thể hiển thị công việc theo tuần, ngược lại trả về vị
     *         trí của công việc đầu tiên gây ra lỗi không thể hiển thị theo tuần.
     */

    struct tm tm_date = {0}; // Khởi tạo struct tm với các thành phần bằng 0.
    strptime(date, "%A %d %B %Y", &tm_date); // Chuyển đổi chuỗi ngày tháng thành struct tm.

    int first_day_of_week = tm_date.tm_mday - tm_date.tm_wday; // Tìm ngày đầu tuần.
    int last_day_of_week = first_day_of_week + 6; // Tìm ngày cuối tuần.

    // In ra thông báo về tuần.
    printf("Cac cong viec trong tuan tu %d/%d/%d den %d/%d/%d:\n",
           tm_date.tm_mday, tm_date.tm_mon + 1, tm_date.tm_year + 1900,
           last_day_of_week, tm_date.tm_mon + 1, tm_date.tm_year + 1900);

    int num_invalid = 0; // Số lượng công việc không nằm trong tuần.

    for (int i = 0; i < no_tasks; i++) {
        struct tm tm_task = {0};
        strptime(array_tasks[i].time, "%A %d %B %Y", &tm_task);

        if (tm_task.tm_mday >= first_day_of_week && tm_task.tm_mday <= last_day_of_week &&
            tm_task.tm_mon == tm_date.tm_mon && tm_task.tm_year == tm_date.tm_year) {
            // Nếu công việc nằm trong tuần, in ra thông tin của công việc.
            printf("Cong viec: %d:\n", i + 1);
            printf("Tieu de: %s\n", array_tasks[i].title);
            printf("Mo ta: %s\n", array_tasks[i].description);
            printf("Thoi gian: %s\n", array_tasks[i].time);
            printf("Trang thai: %s\n\n", getStatusString(array_tasks[i].status));

        } else {
            num_invalid++; // Cộng vào số lượng công việc không nằm trong tuần.
        }
    }

    return num_invalid > 0 ? 0 : -1; // Trả về kết quả tương ứng.
}


int main() {
    struct Task tasks[MAX_TASKS];
    int num_tasks = 0;

    while (1) {
        char command[MAX_COMMAND_LENGTH];
        printf("\nNhap lenh: ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        // Xử lý lệnh "Add".
        if (getCommandType(command) == ADD) {
            char title[MAX_TITLE_LENGTH];
            char description[MAX_DESCRIPTION_LENGTH];
            char time[MAX_TIME_LENGTH];

            getTitleFromAdd(command, title);
            getDescriptionFromAdd(command, description);
            getTimeFromAdd(command, time);

            if (checkTitle(title) && checkDescription(description) && checkTime(time)) {
                if (addTask(tasks, &num_tasks, title, description, time)) {
                    printf("Them cong viec thanh cong.\n");
                } else {
                    printf("Khong the them cong viec. Danh sach cong viec da day.\n");
                }
            } else {
                printf("Du lieu khong hop le.\n");
            }
        }

        // Xử lý lệnh "Show".
        else if (getCommandType(command) == SHOW) {
            printAllTasks(tasks, num_tasks);
        }

        // Xử lý lệnh "Quit".
        else if (getCommandType(command) == QUIT) {
            break;
        }

        // Xử lý lệnh không hợp lệ.
        else {
            printf("Lenh khong hop le.\n");
        }
    }

    return 0;
}