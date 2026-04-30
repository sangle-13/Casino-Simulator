import pandas as pd
import matplotlib.pyplot as plt
import glob
import os
import numpy as np

print("\n" + "="*50)
print(" KỊCH BẢN 1: BẦU CUA - NHÀ CÁI VỐN NHỎ ")
print("="*50)

script_dir = os.path.dirname(os.path.abspath(__file__))
data_dir = os.path.join(script_dir, '..', 'data')

file_list = glob.glob(os.path.join(data_dir, 'data_nho_*.csv'))

if not file_list:
    print(f"LOI: khong tim thay du lieu tai: {data_dir}")
    exit()

all_dfs = []
max_rounds = 0

print(f"[1/3] dang xu ly {len(file_list)} luong du lieu...")
for f in file_list:
    df = pd.read_csv(f)
    all_dfs.append(df)
    max_rounds = max(max_rounds, df['Van'].max())

van_range = np.arange(1, max_rounds + 1)
sum_von_chungthuy = np.zeros(max_rounds)
sum_von_raitham = np.zeros(max_rounds)
sum_von_nhacai = np.zeros(max_rounds)

for df in all_dfs:
    v_ct = df['Von_ChungThuy'].values
    v_rt = df['Von_RaiTham'].values
    v_nc = df['Von_NhaCai'].values
    
    l = len(df)
    
    sum_von_chungthuy[:l] += v_ct
    sum_von_raitham[:l] += v_rt
    sum_von_nhacai[:l] += v_nc
    
    if l < max_rounds:
        tien_cuoi_ct = v_ct[-1]
        tien_cuoi_rt = v_rt[-1]
        tien_cuoi_nc = v_nc[-1]
        
        sum_von_chungthuy[l:] += tien_cuoi_ct
        sum_von_raitham[l:] += tien_cuoi_rt
        sum_von_nhacai[l:] += tien_cuoi_nc

mean_chungthuy = sum_von_chungthuy / len(all_dfs)
mean_raitham = sum_von_raitham / len(all_dfs)
mean_nhacai = sum_von_nhacai / len(all_dfs)

all_dfs_sorted = sorted(all_dfs, key=len)
df_short = all_dfs_sorted[0]
df_long = all_dfs_sorted[-1]

fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(15, 18), layout="constrained")

ax1.plot(df_short['Van'], df_short['Von_ChungThuy'], color='#d62728', label='Chung Thủy', linewidth=1.5)
ax1.plot(df_short['Van'], df_short['Von_RaiTham'], color='#1f77b4', label='Rải Thảm', alpha=0.6)
ax1.plot(df_short['Van'], df_short['Von_NhaCai'], color='black', label='Nhà Cái', linestyle='--', linewidth=2)
ax1.set_title(f"NHANH NHẤT: KẾT THÚC TẠI VÁN: {len(df_short):,}", fontsize=16, fontweight='bold', color='red', pad=15)
ax1.legend(loc='upper right')

ax2.plot(df_long['Van'], df_long['Von_ChungThuy'], color='#d62728', label='Chung Thủy', linewidth=1.2)
ax2.plot(df_long['Van'], df_long['Von_RaiTham'], color='#1f77b4', label='Rải Thảm', alpha=0.6)
ax2.plot(df_long['Van'], df_long['Von_NhaCai'], color='black', label='Nhà Cái', linestyle='--', linewidth=2)
ax2.set_title(f"LÂU NHẤT: KẾT THÚC TẠI VÁN: {len(df_long):,}", fontsize=16, fontweight='bold', color='green', pad=15)
ax2.legend(loc='upper right')

ax3.plot(van_range, mean_chungthuy, color='#d62728', linewidth=2.5, label='Kỳ vọng Chung Thủy')
ax3.plot(van_range, mean_raitham, color='#1f77b4', linewidth=2.5, label='Kỳ vọng Rải Thảm')
ax3.plot(van_range, mean_nhacai, color='black', linewidth=3, label='Kỳ Vọng Nhà Cái', linestyle='--')
ax3.fill_between(van_range, mean_chungthuy, color='#d62728', alpha=0.1)
ax3.set_title("ĐƯỜNG CONG KỲ VỌNG TRUNG BÌNH (EV)", fontsize=16, fontweight='bold', color='purple', pad=15)
ax3.set_xlabel("Số lượng ván cược", fontsize=12)

for ax in [ax1, ax2, ax3]:
    ax.axhline(0, color='black', linestyle='-', linewidth=1.5) 
    ax.set_ylabel("Số dư trong ví (VNĐ)", fontsize=12)
    ax.grid(True, linestyle=':', alpha=0.5)

fig.suptitle('KỊCH BẢN 1: BẦU CUA - NHÀ CÁI VỐN NHỎ ', fontsize=22, fontweight='bold')
print("[3/3] Hoan tat! Bieu do da duoc hien thi.")
plt.show()