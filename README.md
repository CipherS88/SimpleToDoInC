<div align="center">

# ✨ C To-Do List Manager

### *Linked lists, pointers, and a surprisingly cute terminal*

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Deps](https://img.shields.io/badge/Dependencies-none-3fb950?style=for-the-badge)
![Vibes](https://img.shields.io/badge/Vibes-Immaculate-ff8ab3?style=for-the-badge)

> *A console todo app in pure C: saves between sessions, runs anywhere, and frees everything on exit.*

</div>

---

## ☁️ About

No dependencies, just vibes and pointers. Tasks live in a linked list in memory and are written to `tasks.txt` in a simple pipe-separated format, so the file stays readable and diffable.

---

## ✨ Features

- 📝 **Task management** — add, view, edit, delete and complete tasks.
- 💾 **Auto-save** — writes to `tasks.txt` automatically.
- 💻 **Cross-platform** — Windows, Linux and macOS with the same source.
- 🧹 **Clean memory** — every node is freed on exit, no leaks left behind.

---

## 🌸 Compile & run

**1. Compile:**

```bash
gcc -o todo todo.c
```

**2. Run:**

```bash
./todo          # Linux / macOS
todo.exe        # Windows
```

That's it — no flags, no config, no build system.

---

## 📂 Layout

```text
todo.c        الكود الكامل (قائمة مرتبطة + قائمة الترمينال)
doc.html      التوثيق المرئي للمشروع
tasks.txt     يُنشأ تلقائيًا عند أول حفظ
```

---

## 🧠 Notes

- الملف يُنشأ في نفس مجلد التشغيل — شغّل البرنامج من المجلد الذي تريد الحفظ فيه.
- الصيغة أنبوبية (`title|done|id`)، لذلك يمكن تعديل الملف يدويًا بدون كسر البرنامج.

---

<div align="center">

<sub>Built by <b>Abdullah Aljuaid</b> · <a href="https://github.com/CipherS88">@CipherS88</a></sub>

</div>
