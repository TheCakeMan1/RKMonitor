# 🚀 RKMonitor — Текстовый мониторинг системы на Orange Pi

RKMonitor — это легковесный мониторинг системы на **C** с использованием **ncurses**. Позволяет отслеживать загрузку процессора, состояние памяти и другую системную информацию прямо в терминале.

![image](https://github.com/user-attachments/assets/70ef4d98-1d2d-4eb5-9def-c0287efb9716)
![image](https://github.com/user-attachments/assets/8a5b2a38-b307-4da9-acdd-6a779f69a2c0)

---

## 📦 Установка

### 🏗 **Сборка из исходников**
> Поддерживаются **Linux**, **Orange Pi**, возможно **Raspberry Pi**.

1. Установите **ncurses** (если не установлена):
   ```sh
   sudo apt install libncurses-dev
   ```
2. Клонируйте репозиторий:
   ```sh
   git clone https://github.com/TheCakeMan1/RKMonitor.git
   cd RKMonitor
   ```
3. Скомпилируйте:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
4. Запустите программу(обязательно от sudo):
   ```sh
   sudo ./rock-monitor
   ```
## 🔧 Функции
✅ Отображение загрузки процессора  
✅ Мониторинг оперативной памяти  
✅ Вывод информации сопроцессорах NPU и VPU, а также RGA   
✅ Минимальная нагрузка на систему так как написана на C  
✅ Оптимизировано для Orange Pi  
## 🛠 Разработка
Хотите внести свой вклад? Отлично! Форкните репозиторий, внесите изменения и создайте Pull Request.
   ```
   git clone https://github.com/TheCakeMan1/RKMonitor.git
   cd RKMonitor
   git checkout -b my-feature-branch
   ```
## 📜 Лицензия
Проект распространяется под лицензией MIT – свободно используйте, модифицируйте и распространяйте.  
👤 Автор: TheCakeMan1  
📧 Контакт: lilo.lilo565@gmail.com  
