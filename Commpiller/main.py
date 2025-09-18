import tkinter as tk
from tkinter import filedialog, messagebox

def compile_file(input_path, output_path, key=123):
    try:
        with open(input_path, 'r', encoding='utf-8') as f:
            data = f.read().encode('utf-8')

        binary_data = bytes([b ^ key for b in data])

        with open(output_path, 'wb') as f:
            f.write(binary_data)

        messagebox.showinfo("Готово", f"The file has been compiled successfully:\n{output_path}")
    except Exception as e:
        messagebox.showerror("Error:", str(e))

def choose_file():
    input_path = filedialog.askopenfilename(filetypes=[("VME files", "*.vme")])
    if input_path:
        output_path = filedialog.asksaveasfilename(defaultextension=".vbm", filetypes=[("VBM files", "*.vbm")])
        if output_path:
            compile_file(input_path, output_path)

root = tk.Tk()
root.title("Compiller")

frame = tk.Frame(root, padx=20, pady=20)
frame.pack()

label = tk.Label(frame, text="Select the file .vme for compilation:")
label.pack(pady=10)

button = tk.Button(frame, text="Select file", command=choose_file)
button.pack(pady=10)

root.mainloop()
