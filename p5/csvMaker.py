import csv

def main():
   fields = []
   list_2015_ = []
   list_2016_ = []
   list_2017_ = []
   list_2018_ = []
   list_2019_ = []

   with open('county_demographics.csv', mode='r') as file_2020_,\
        open('county_demographics2014.csv', mode='r') as file_2014_:
        
      reader_2020_ = csv.reader(file_2020_, delimiter=',')
      reader_2014_ = csv.reader(file_2014_, delimiter=',')
      line_count_ = 0

      for row_2020_, row_2014_ in zip(reader_2020_, reader_2014_):
         temp1 = []
         temp2 = []
         temp3 = []
         temp4 = []
         temp5 = []

         if line_count_ == 0:
            # print(f'2020 Column names are {", ".join(row_2020_)}\n')
            # print(f'2014 Column names are {", ".join(row_2014_)}')
            line_count_ += 1
            fields = row_2020_
         else:
            idx = 0
            for cell_2020_, cell_2014_ in zip(row_2020_, row_2014_):
               intSet = {7, 17, 18, 19, 21, 22, 30, 31, 32, 34, 35, 36, 37, 38, 39, 40, 41, 42}

               if (idx == 0) or (idx == 1):
                  temp1.append(cell_2020_)
                  temp2.append(cell_2020_)
                  temp3.append(cell_2020_)
                  temp4.append(cell_2020_)
                  temp5.append(cell_2020_)

               elif idx in intSet:
                  int_val_2020_ = int(cell_2020_)
                  int_val_2014_ = int(cell_2014_) 
                  yearly_inc_ = int((int_val_2020_ - int_val_2014_) / 6)

                  temp1.append(str((yearly_inc_ * 1) + int_val_2014_))
                  temp2.append(str((yearly_inc_ * 2) + int_val_2014_))
                  temp3.append(str((yearly_inc_ * 3) + int_val_2014_))
                  temp4.append(str((yearly_inc_ * 4) + int_val_2014_))
                  temp5.append(str((yearly_inc_ * 5) + int_val_2014_))
               else:
                  double_val_2020_ = float(cell_2020_)
                  double_val_2014_ = float(cell_2014_) 
                  yearly_inc_ = float((double_val_2020_ - double_val_2014_) / 6)

                  temp1.append(str((yearly_inc_ * 1) + double_val_2014_))
                  temp2.append(str((yearly_inc_ * 2) + double_val_2014_))
                  temp3.append(str((yearly_inc_ * 3) + double_val_2014_))
                  temp4.append(str((yearly_inc_ * 4) + double_val_2014_))
                  temp5.append(str((yearly_inc_ * 5) + double_val_2014_))

               
               idx += 1
               line_count_ += 1
            list_2015_.append(temp1)
            list_2016_.append(temp2)
            list_2017_.append(temp3)
            list_2018_.append(temp4)
            list_2019_.append(temp5)

         print(line_count_)

   filenames = ["county_demographics2015.csv", "county_demographics2016.csv", 
                "county_demographics2017.csv", "county_demographics2018.csv", 
                "county_demographics2019.csv"]

   with open(filenames[0], "w") as out_2015_,\
        open(filenames[1], "w") as out_2016_,\
        open(filenames[2], "w") as out_2017_,\
        open(filenames[3], "w") as out_2018_,\
        open(filenames[4], "w") as out_2019_:

      csvwriter1 = csv.writer(out_2015_)
      csvwriter1.writerow(fields)
      csvwriter1.writerows(list_2015_)

      csvwriter2 = csv.writer(out_2016_)
      csvwriter2.writerow(fields)
      csvwriter2.writerows(list_2016_)

      csvwriter3 = csv.writer(out_2017_)
      csvwriter3.writerow(fields)
      csvwriter3.writerows(list_2017_)

      csvwriter4 = csv.writer(out_2018_)
      csvwriter4.writerow(fields)
      csvwriter4.writerows(list_2018_)

      csvwriter5 = csv.writer(out_2019_)
      csvwriter5.writerow(fields)
      csvwriter5.writerows(list_2019_)

                  

if __name__ == "__main__":
   main()
