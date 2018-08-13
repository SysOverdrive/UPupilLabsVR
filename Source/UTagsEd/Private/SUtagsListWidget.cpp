
#include "SUtagsListWidget.h"

#define LOCTEXT_NAMESPACE "SUtagsListWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUtagsListWidget::Construct(const FArguments& Args)
{
	//std::string "Add New Item To List" = "Add New Item To List";
	const FString ButtonFString("Add New Item To List");
	const FText ButtonFText = FText::FromString(ButtonFString);

	TSharedRef<SScrollBar> ScrollBar = SNew(SScrollBar) //Todod 
		.Orientation(EOrientation::Orient_Vertical)
		.Visibility(EVisibility::Visible)
		.AlwaysShowScrollbar(true);

	ChildSlot
		[

			SNew(SBox)
			//	.MaxDesiredHeight(ChildSlot) FOR SCROLLBAR WE MUST GET THE SIZE OF THE CHILDREN AND SET IT TO THE MAXIMUM OF THE WINDOW
		[
			SNew(SScrollBox)
			.ExternalScrollbar(ScrollBar)

		+ SScrollBox::Slot()[
	
			SNew(SSearchBox)
				.HintText(LOCTEXT("SearchBoxHint", "Search after object name"))
				.OnTextChanged(this, &SUtagsListWidget::HandleFilterStringTextChanged)
				
		]
		+ SScrollBox::Slot()
				[
					SNew(SButton)
					.Text(ButtonFText)
				.OnClicked(this, &SUtagsListWidget::ButtonPressed)
				]
				+ SScrollBox::Slot()
					[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.FillWidth(1)
					[
						SAssignNew(ItemsPanel, SListPanel)
						.ItemWidth(InItemWidth)
					.ItemHeight(InItemHeight)
					.NumDesiredItems(this, &STableViewBase::GetNumItemsBeingObserved)
					.ItemAlignment(InItemAlignment)
					]
					]

				//	[
				//		SNew(SSplitter).ResizeMode(ESplitterResizeMode::Fill)
				//		+ SSplitter::Slot()
				//	[
				//		SAssignNew(FirstViewWidget, SListView<TSharedPtr<FString>>)
				//		.ItemHeight(22)
				//	.ListItemsSource(&ItemsFirstColumn) //The Items array is the source of this listview
				//	.OnGenerateRow(this, &SUtagsListWidget::OnGenerateRowForList)
				//	.HeaderRow(
				//		SNew(SHeaderRow)
				//		+ SHeaderRow::Column("FirstHeaderRow")
				//		.FillWidth(1)
				//		[
				//			SNew(STextBlock)
				//			.Text(FText::FromString("Object/Type"))
				//		]
				//	)
				//	]
				//	+ SSplitter::Slot()
				//	[
				//	SAssignNew(SecondViewWidget, SListView<TSharedPtr<FString>>)
				//	.ItemHeight(22)
				//	.ListItemsSource(&ItemsSecondColumn) //The Items array is the source of this listview
				//	.OnGenerateRow(this, &SUtagsListWidget::OnGenerateRowForEditableList)
				//	.HeaderRow(
				//		SNew(SHeaderRow)
				//		+ SHeaderRow::Column("SecondHeaderRow")
				//		[
				//			SNew(STextBlock)
				//			.Text(FText::FromString("Key Value Tags"))
				//		]
				//	)

				//	]
				//]
			]
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
FReply SUtagsListWidget::ButtonPressed()
{
	//Adds a new item to the array (do whatever you want with this)
	ItemsFirstColumn.Add(MakeShareable(new FString("Object/TagType")));
	ItemsSecondColumn.Add(MakeShareable(new FString("Key Value List Of Tags")));

	//Update the listview
	FirstViewWidget->RequestListRefresh();
	SecondViewWidget->RequestListRefresh();

	return FReply::Handled();
}

TSharedRef<ITableRow> SUtagsListWidget::OnGenerateRowForList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	//Create the row
	return
		SNew(STableRow< TSharedPtr<FString> >, OwnerTable)
		.Padding(2.0f)
		
		[
			SNew(STextBlock).Text(FText::FromString(*Item.Get()))
		];
}

TSharedRef<ITableRow> SUtagsListWidget::OnGenerateRowForEditableList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	//Create the row
	
		TSharedRef<ITableRow> EditableRow = SNew(STableRow< TSharedPtr<SEditableTextBox> >, OwnerTable)
		.Padding(2.0f)
			[			
			SNew(SEditableTextBox).Text(FText::FromString(*Item.Get()))	
			];

		
		return EditableRow;
}

#undef LOCTEXT_NAMESPACE