import cv2

def main():
    # Read the input image
    image = cv2.imread("test_image.jpg")

    # Check if the image was successfully loaded
    if image is None:
        print("Error: Couldn't open or find the image.")
        return

    # Define the cropping region
    x = (image.shape[1] - 724) // 2  # Center crop for width
    y = (image.shape[0] - 715) // 2  # Center crop for height
    width = 724
    height = 715

    # Crop the image
    cropped_image = image[y:y+height, x:x+width]

    # Save the cropped image
    cv2.imwrite("cropped_image.jpg", cropped_image)

    print("Cropped image saved successfully.")

if __name__ == "__main__":
    main()



#replace
# height 2749px , width 2769px